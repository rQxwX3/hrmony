#include <keys.hpp>
#include <macos.hpp>
#include <utility.hpp>

#include <iostream>

using Keys::Modifiers;
using macOS::MacOS;

auto macOS::util::isHRMModeExitTriggered(const MacOS *self, const Event &event)
    -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto config{self->getConfig()};

    auto const nativeKey{static_cast<NativeKeyCode>(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode))};

    auto const printableKey{self->nativeKey2Printable(nativeKey)};

    return printableKey == config.exitKey;
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

auto macOS::util::getBindedCombination(const MacOS *self, const Event &event)
    -> Combination {
    const auto nativeKey{static_cast<NativeKeyCode>(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode))};

    return self->getKeyBinding(self->nativeKey2Printable(nativeKey));
}

auto macOS::util::isBindedKeyPressed(const MacOS *self, const Event &event)
    -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto &bindedCombination{getBindedCombination(self, event)};

    return !bindedCombination.isEmpty() && !bindedCombination.isNoModifiers();
}

auto macOS::util::isKeymapFinished(const MacOS *self, const Event &event)
    -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto &bindedCombination{getBindedCombination(self, event)};

    return bindedCombination.isEmpty() || bindedCombination.isNoModifiers();
}

auto macOS::util::processKeyPress(CGEventTapProxy proxy, CGEventType type,
                                  CGEventRef event, void *refcon)
    -> CGEventRef {
    auto *self{static_cast<MacOS *>(refcon)};

    if (self->isHRMMode() && !self->isLeaderUpProcessed()) {
        std::cout << "leader key processed\n";
        self->toggleLeaderUpProcessed();
        return nullptr;
    }

    if (isHRMModeEnterTriggered(self, event)) {
        std::cout << "entering HRM\n";
        self->enterHRMMode();

        return nullptr;
    }

    if (isHRMModeExitTriggered(self, event)) {
        std::cout << "exiting HRM\n";
        self->exitHRMMode();

        return nullptr;
    }

    if (isBindedKeyPressed(self, event)) {
        std::cout << "binded keypress\n";

        self->addToCurrentCombination(getBindedCombination(self, event));

        return nullptr;
    }

    if (isKeymapFinished(self, event)) {
        std::cout << "keymap finished\n";

        self->addToCurrentCombination(getBindedCombination(self, event));
        self->setEventToCurrentCombination(event);
        self->toggleLeaderUpProcessed();
        self->exitHRMMode();
    }

    return event;
}
