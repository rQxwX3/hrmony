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

auto mac::util::isBindedKeyPressed(const MacOS *self,
                                   const comb::Combination &combination)
    -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    return combination.containsNoRegulars() && !combination.isEmpty() &&
           !combination.containsNoModifiers();
}

auto mac::util::isSyntheticEvent(const Event &event) -> bool {
    return CGEventGetIntegerValueField(event, kCGEventSourceUserData) ==
           mac::util::kSyntheticTag;
}

auto mac::util::isKeymapFinished(const MacOS *self,
                                 const comb::Combination &combination) -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    return combination.isEmpty() || !combination.containsNoRegulars();
}

auto mac::util::processNoModifiersBinding(MacOS *self, Event &event,
                                          const comb::Combination &binding)
    -> void {
    self->addToCurrentCombination(binding);
    self->setEventToCombination(event, self->getCurrentCombination());
    self->toggleLeaderUpProcessed();
    self->exitHRMMode();
}

auto mac::util::processEmptyBinding(MacOS *self, Event &event,
                                    const comb::Combination &binding) -> void {
    const auto nativeCodeCombination{
        createCombinationFromNativeCode(self, self->getCurrentNativeCode())};

    self->addToCurrentCombination(nativeCodeCombination);

    self->setEventToCombination(event, self->getCurrentCombination());
    self->toggleLeaderUpProcessed();
    self->exitHRMMode();
}

auto mac::util::processMultipleRegularsBinding(MacOS *self,
                                               const comb::Combination &binding)
    -> void {
    const auto modifiers{binding.getModifiers()};
    const auto [regularsArray, regularsCount]{binding.getRegulars()};

    for (size_t i{0}; i != regularsCount; ++i) {
        const auto regular{regularsArray.at(i)};
        const auto nativeCode{self->keyToNativeCode(regular)};

        createAndPostKeyboardEvent(self, nativeCode, modifiers, true,
                                   mac::util::kSyntheticTag);
        createAndPostKeyboardEvent(self, nativeCode, modifiers, false,
                                   mac::util::kSyntheticTag);
    }

    self->toggleLeaderUpProcessed();
    self->exitHRMMode();
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

    const auto currentBinding{self->getBindedCombinations()};

    if (currentBinding.count == 1) {
        const auto combination{currentBinding.array.at(0)};

        if (isBindedKeyPressed(self, combination)) {
            std::cout << "binded key press\n";
            self->addToCurrentCombination(combination);

            return nullptr;
        }

        if (isKeymapFinished(self, combination)) {
            std::cout << "keymap finished\n";

            if (combination.containsMultipleRegulars()) {
                processMultipleRegularsBinding(self, combination);

                return nullptr;
            }

            if (combination.containsNoModifiers()) {
                if (combination.isEmpty()) {
                    processEmptyBinding(self, event, combination);
                } else {
                    processNoModifiersBinding(self, event, combination);
                }
            }
        }

        return event;
    }

    for (size_t i{0}; i != currentBinding.count; ++i) {
        const auto combination{currentBinding.array.at(i)};

        for (size_t j{0}; j != combination.getRegulars().count; ++j) {
            const auto nativeCode{
                self->keyToNativeCode(combination.getRegulars().array.at(j))};

            createAndPostKeyboardEvent(self, nativeCode,
                                       combination.getModifiers(), true,
                                       kSyntheticTag);

            createAndPostKeyboardEvent(self, nativeCode,
                                       combination.getModifiers(), false,
                                       kSyntheticTag);
        }
    }

    return nullptr;
}
