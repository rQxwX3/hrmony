#include <keys.hpp>
#include <macos.hpp>
#include <utility.hpp>

#include <iostream>

using key::Keys;
using mac::MacOS;

auto mac::util::createAndPostKeyboardEvent(
    const MacOS *self, const NativeCode nativeCode,
    const comb::types::Modifiers modifiers, bool isDown) -> void {
    auto *event{CGEventCreateKeyboardEvent(nullptr, nativeCode, isDown)};

    self->setEventFlagsToModifiers(event, modifiers);

    CGEventPost(kCGHIDEventTap, event);

    CFRelease(event);
}

auto mac::util::isHRMModeExitTriggered(const MacOS *self) -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto exitKey{self->getConfig().exitKey};
    const auto nativeCode{self->getCurrentNativeCode()};

    // TODO Only works if exitKey is a key
    return self->nativeCodeToKey(nativeCode) == self->getConfig().exitKey;
}

auto mac::util::isHRMModeEnterTriggered(const MacOS *self) -> bool {
    if (self->isHRMMode()) {
        return false;
    }

    const auto leaderKey{self->getConfig().leaderKey};
    const auto nativeCode{self->getCurrentNativeCode()};

    // TODO Only works if leaderKey is a modifier (maybe create a single
    // conversion function for both types)
    return self->nativeCodeToKey(nativeCode) == leaderKey;
}

auto mac::util::isBindedKeyPressed(const MacOS *self) -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto &bindedCombination{self->getCurrentCombination()};

    return !bindedCombination.isEmpty() &&
           !bindedCombination.containsNoModifiers();
}

auto mac::util::isKeymapFinished(const MacOS *self) -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto &bindedCombination{self->getCurrentCombination()};

    return bindedCombination.isEmpty() ||
           bindedCombination.containsNoModifiers();
}

auto mac::util::addKeyToFinishedKeymap(MacOS *self) -> void {
    comb::Combination combination(self->getCurrentCombination());

    if (combination.containsNoModifiers()) {
        const auto &combination{self->getCurrentCombination()};
    } else {
        const auto nativeCode{self->getCurrentNativeCode()};

        // TODO Only supports addition of one key
        combination = comb::Combination({self->nativeCodeToKey(nativeCode)}, 1);
    }

    self->addToCurrentCombination(combination);
}

[[nodiscard]] auto mac::util::isProcessingLeaderUp(const MacOS *self) -> bool {
    if (self->isLeaderUpProcessed()) {
        return false;
    }

    if (!self->isHRMMode()) {
        return false;
    }

    const auto config{self->getConfig()};
    const auto nativeCode{self->getCurrentNativeCode()};

    return config.leaderKey == self->nativeCodeToKey(nativeCode);
}

auto mac::util::processKeyPress(CGEventTapProxy proxy, CGEventType type,
                                CGEventRef event, void *refcon) -> CGEventRef {
    auto *self{static_cast<MacOS *>(refcon)};

    self->setCurrentCombination(self->getBindedCombination());

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
        self->addToCurrentCombination(self->getCurrentCombination());

        return nullptr;
    }

    if (isKeymapFinished(self)) {
        std::cout << "keymap finished\n";

        auto currentCombination{self->getCurrentCombination()};

        if (currentCombination.containsMultipleRegulars()) {
            const auto modifiers{currentCombination.getModifiers()};
            const auto [regularsArray,
                        regularsCount]{currentCombination.getRegulars()};

            for (size_t i{0}; i != regularsCount; ++i) {
                const auto regular{regularsArray.at(i)};
                const auto nativeCode{self->keyToNativeCode(regular)};

                createAndPostKeyboardEvent(self, nativeCode, modifiers, true);
                createAndPostKeyboardEvent(self, nativeCode, modifiers, false);
            }

            return nullptr;
        }

        if (currentCombination.isEmpty()) {
            self->setCurrentCombinationToCurrentNativeCode();
        }

        self->setEventToCurrentCombination(event);
        self->toggleLeaderUpProcessed();
        self->exitHRMMode();
    }

    return event;
}
