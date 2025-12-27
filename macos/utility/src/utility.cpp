#include <keys.hpp>
#include <macos.hpp>
#include <utility.hpp>

#include <iostream>

using key::Modifiers;
using macOS::MacOS;

auto macOS::util::getBindedCombination(const MacOS *self, const Event &event)
    -> Combination {
    const auto nativeKey{static_cast<NativeKeyCode>(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode))};

    return self->getKeyBinding(self->nativeKeyToPrintable(nativeKey));
}

auto macOS::util::isHRMModeExitTriggered(const MacOS *self) -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto config{self->getConfig()};

    auto const nativeKey{self->getCurrentNativeCode()};

    auto const printableKey{self->nativeKeyToPrintable(nativeKey)};

    return printableKey == config.exitKey;
}

auto macOS::util::isHRMModeEnterTriggered(const MacOS *self) -> bool {
    if (self->isHRMMode()) {
        return false;
    }

    const auto config{self->getConfig()};

    const auto leaderKey{config.leaderKey};

    const auto nativeCode{self->getCurrentNativeCode()};

    return self->nativeCodeToModifier(nativeCode) == leaderKey;
}

auto macOS::util::isBindedKeyPressed(const MacOS *self) -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto &bindedCombination{self->getCurrentBindedCombination()};

    return !bindedCombination.isEmpty() && !bindedCombination.isNoModifiers();
}

auto macOS::util::isKeymapFinished(const MacOS *self) -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto &bindedCombination{self->getCurrentBindedCombination()};

    return bindedCombination.isEmpty() || bindedCombination.isNoModifiers();
}

auto macOS::util::addKeyToFinishedKeymap(MacOS *self) -> void {
    Combination combination(self->getCurrentBindedCombination());

    if (combination.isNoModifiers()) {
        const auto &combination{self->getCurrentBindedCombination()};
    } else {
        const auto nativeKey{self->getCurrentNativeCode()};

        combination = Combination({nativeCodeToKey.at(nativeKey)}, 1);
    }

    self->addToCurrentCombination(combination);
}

[[nodiscard]] auto macOS::util::isProcessingLeaderUp(const MacOS *self)
    -> bool {
    if (self->isLeaderUpProcessed()) {
        return false;
    }

    if (!self->isHRMMode()) {
        return false;
    }

    const auto config{self->getConfig()};
    const auto nativeCode{self->getCurrentNativeCode()};

    return config.leaderKey == self->nativeCodeToModifier(nativeCode);
}

auto macOS::util::processKeyPress(CGEventTapProxy proxy, CGEventType type,
                                  CGEventRef event, void *refcon)
    -> CGEventRef {
    auto *self{static_cast<MacOS *>(refcon)};

    const auto &bindedCombination(getBindedCombination(self, event));

    self->setCurrentBindedCombination(bindedCombination);
    self->setCurrentNativeCode(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));

    if (isProcessingLeaderUp(self)) {
        std::cout << "leader key processed\n";
        self->toggleLeaderUpProcessed();
        return nullptr;
    }

    if (isHRMModeEnterTriggered(self)) {
        std::cout << "entering HRM\n";
        self->enterHRMMode();

        return nullptr;
    }

    if (isHRMModeExitTriggered(self)) {
        std::cout << "exiting HRM\n";
        self->exitHRMMode();

        return nullptr;
    }

    if (isBindedKeyPressed(self)) {
        std::cout << "binded keypress\n";

        self->addToCurrentCombination(getBindedCombination(self, event));

        return nullptr;
    }

    if (isKeymapFinished(self)) {
        std::cout << "keymap finished\n";

        addKeyToFinishedKeymap(self);
        self->setEventToCurrentCombination(event);
        self->toggleLeaderUpProcessed();
        self->exitHRMMode();
    }

    return event;
}
