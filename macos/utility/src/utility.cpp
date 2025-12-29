#include <keys.hpp>
#include <macos.hpp>
#include <utility.hpp>

#include <iostream>

using key::Modifiers;
using macOS::MacOS;

auto macOS::util::getBindedCombination(const MacOS *self) -> Combination {
    const auto nativeCode{self->getCurrentNativeCode()};

    return self->getKeyBinding(self->nativeCodeToKey(nativeCode));
}

auto macOS::util::isHRMModeExitTriggered(const MacOS *self) -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto exitKey{self->getConfig().exitKey};
    const auto nativeCode{self->getCurrentNativeCode()};

    // TODO Only works if exitKey is a key
    return self->nativeCodeToKey(nativeCode) == self->getConfig().exitKey;
}

auto macOS::util::isHRMModeEnterTriggered(const MacOS *self) -> bool {
    if (self->isHRMMode()) {
        return false;
    }

    const auto leaderKey{self->getConfig().leaderKey};
    const auto nativeCode{self->getCurrentNativeCode()};

    // TODO Only works if leaderKey is a modifier (maybe create a single
    // conversion function for both types)
    return self->nativeCodeToModifier(nativeCode) == leaderKey;
}

auto macOS::util::isBindedKeyPressed(const MacOS *self) -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto &bindedCombination{getBindedCombination(self)};

    return !bindedCombination.isEmpty() && !bindedCombination.isNoModifiers();
}

auto macOS::util::isKeymapFinished(const MacOS *self) -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto &bindedCombination{getBindedCombination(self)};

    return bindedCombination.isEmpty() || bindedCombination.isNoModifiers();
}

auto macOS::util::addKeyToFinishedKeymap(MacOS *self) -> void {
    Combination combination(getBindedCombination(self));

    if (combination.isNoModifiers()) {
        const auto &combination{getBindedCombination(self)};
    } else {
        const auto nativeCode{self->getCurrentNativeCode()};

        // TODO Only supports addition of one key
        combination = Combination({nativeCodeToKey.at(nativeCode)}, 1);
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

    const auto &bindedCombination(getBindedCombination(self));

    self->setCurrentNativeCode(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));

    if (isProcessingLeaderUp(self)) {
        std::cout << "processing leader up\n";
        self->toggleLeaderUpProcessed();

        return nullptr;
    }

    if (isHRMModeEnterTriggered(self)) {
        std::cout << "entering hrm mode\n";
        self->enterHRMMode();

        return nullptr;
    }

    if (isHRMModeExitTriggered(self)) {
        std::cout << "exiting hrm mode\n";
        self->exitHRMMode();

        return nullptr;
    }

    if (isBindedKeyPressed(self)) {
        std::cout << "binded key press\n";
        self->addToCurrentCombination(getBindedCombination(self));

        return nullptr;
    }

    if (isKeymapFinished(self)) {
        std::cout << "keymap finished\n";
        addKeyToFinishedKeymap(
            self); // for key-key remaps (does nothing otherwise)

        self->setEventToCurrentCombination(event);
        self->toggleLeaderUpProcessed();
        self->exitHRMMode();
    }

    return event;
}
