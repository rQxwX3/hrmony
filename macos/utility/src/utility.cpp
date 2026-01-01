#include <keys.hpp>
#include <macos.hpp>
#include <utility.hpp>

#include <iostream>

using key::Keys;
using mac::MacOS;

auto mac::util::createAndPostKeyboardEvent(
    const MacOS *self, const NativeCode nativeCode,
    const comb::types::Modifiers modifiers, bool isDown, int64_t kSyntheticTag)
    -> void {
    auto *event{CGEventCreateKeyboardEvent(nullptr, nativeCode, isDown)};

    self->setEventFlagsToModifiers(event, modifiers);

    if (kSyntheticTag != 0) {
        CGEventSetIntegerValueField(event, kCGEventSourceUserData,
                                    kSyntheticTag);
    }

    CGEventPost(kCGHIDEventTap, event);

    CFRelease(event);
}

[[nodiscard]] auto mac::util::createCombinationFromNativeCode(
    const MacOS *self, const NativeCode nativeCode) -> comb::Combination {
    const auto key{self->nativeCodeToKey(nativeCode)};

    return comb::Combination({.array = {key}, .count = 1});
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

    const auto &bindedCombination{self->getBindedCombination()};

    return !bindedCombination.isEmpty() &&
           !bindedCombination.containsNoModifiers();
}

auto mac::util::isSyntheticEvent(const Event &event) -> bool {
    return CGEventGetIntegerValueField(event, kCGEventSourceUserData) ==
           mac::util::kSyntheticTag;
}

auto mac::util::isKeymapFinished(const MacOS *self) -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto &bindedCombination{self->getBindedCombination()};

    return bindedCombination.isEmpty() ||
           bindedCombination.containsNoModifiers();
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
    if (isSyntheticEvent(event)) {
        return event;
    }

    auto *self{static_cast<MacOS *>(refcon)};

    self->setCurrentNativeCode(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));

    const auto currentCombination{self->getBindedCombination()};

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
        self->addToCurrentCombination(self->getBindedCombination());

        return nullptr;
    }

    if (isKeymapFinished(self)) {
        std::cout << "keymap finished\n";

        auto currentBinding{self->getBindedCombination()};

        if (currentBinding.containsMultipleRegulars()) {
            const auto modifiers{currentBinding.getModifiers()};
            const auto [regularsArray,
                        regularsCount]{currentBinding.getRegulars()};

            for (size_t i{0}; i != regularsCount; ++i) {
                const auto regular{regularsArray.at(i)};
                const auto nativeCode{self->keyToNativeCode(regular)};

                createAndPostKeyboardEvent(self, nativeCode, modifiers, true,
                                           mac::util::kSyntheticTag);
                createAndPostKeyboardEvent(self, nativeCode, modifiers, false,
                                           mac::util::kSyntheticTag);
            }

            return nullptr;
        }

        if (currentBinding.isEmpty()) {
            const auto nativeCodeCombination{createCombinationFromNativeCode(
                self, self->getCurrentNativeCode())};

            self->addToCurrentCombination(nativeCodeCombination);
        } else if (currentBinding.containsNoModifiers()) {
            self->addToCurrentCombination(currentBinding);
        }

        self->setEventToCombination(event, self->getCurrentCombination());
        self->toggleLeaderUpProcessed();
        self->exitHRMMode();
    }

    return event;
}
