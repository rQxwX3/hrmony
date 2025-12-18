#include <macos.hpp>
#include <utility.hpp>

using macOS::MacOS;

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

auto macOS::util::getBindedModifier(const MacOS *self, const Event &event)
    -> Keys::Modifiers {
    const auto nativeKey{static_cast<NativeKeyCode>(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode))};

    return self->getKeyBinding(self->nativeKey2Printable(nativeKey));
}

auto macOS::util::isBindedKeyPressed(const MacOS *self, const Event &event)
    -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    return Keys::Modifiers::NULLKEY != getBindedModifier(self, event);
}

auto macOS::util::isKeymapFinished(const MacOS *self, const Event &event)
    -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    return Keys::Modifiers::NULLKEY == getBindedModifier(self, event);
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
        self->toggleHRMMode();

        return nullptr;
    }

    if (isBindedKeyPressed(self, event)) {
        const auto bindedModifier{getBindedModifier(self, event)};

        self->addCurrentModifier(bindedModifier);

        return nullptr;
    }

    if (isKeymapFinished(self, event)) {
        self->setEventModifiersToCurrent(event);
        self->toggleLeaderUpProcessed();
        self->toggleHRMMode();
    }

    return event;
}
