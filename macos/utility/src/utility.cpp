#include <keys.hpp>
#include <macos.hpp>
#include <utility.hpp>

#include <algorithm>

using Keys::Modifiers;
using macOS::MacOS;

auto macOS::util::isModifiersArrayEmpty(const ModifiersArray &modifiersArray)
    -> bool {
    return std::ranges::all_of(modifiersArray.begin(), modifiersArray.end(),
                               [](Modifiers modifier) -> bool {
                                   return modifier == Modifiers::NULLKEY;
                               });
}

auto macOS::util::isHRMModeEnterTriggered(const MacOS *self, const Event &event)
    -> bool {
    if (self->isHRMMode()) {
        return false;
    }

    const auto config{self->getConfig()};
    const auto nativeLeaderKey{self->modifier2NativeModifier(config.leaderKey)};

    auto const nativeModifiers{CGEventGetFlags(event)};

    return (nativeModifiers & nativeLeaderKey) != 0U;
}

auto macOS::util::getBindedModifiers(const MacOS *self, const Event &event)
    -> ModifiersArray {
    const auto nativeKey{static_cast<NativeKeyCode>(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode))};

    return self->getKeyBinding(self->nativeKey2Printable(nativeKey));
}

auto macOS::util::isBindedKeyPressed(const MacOS *self, const Event &event)
    -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    return Modifiers::NULLKEY != getBindedModifiers(self, event).at(0);
}

auto macOS::util::isKeymapFinished(const MacOS *self, const Event &event)
    -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    return Modifiers::NULLKEY == getBindedModifiers(self, event).at(0);
}

auto macOS::util::processKeyPress(CGEventTapProxy proxy, CGEventType type,
                                  CGEventRef event, void *refcon)
    -> CGEventRef {
    auto *self{static_cast<MacOS *>(refcon)};

    if (self->isHRMMode() && !self->isLeaderUpProcessed()) {
        self->toggleLeaderUpProcessed();
        return nullptr;
    }

    if (isHRMModeEnterTriggered(self, event)) {
        self->enterHRMMode();

        return nullptr;
    }

    if (isBindedKeyPressed(self, event)) {
        const auto bindedModifier{getBindedModifiers(self, event)};

        self->addModifersArrayToCurrent(bindedModifier);

        return nullptr;
    }

    if (isKeymapFinished(self, event)) {
        self->setEventModifiersToCurrent(event);
        self->toggleLeaderUpProcessed();
        self->exitHRMMode();
    }

    return event;
}
