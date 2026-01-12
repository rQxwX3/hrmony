#include <groupTypes.hpp>
#include <keys.hpp>
#include <macos.hpp>
#include <utility.hpp>

#include <iostream>

using key::Keys;
using mac::MacOS;

auto mac::util::createAndPostKeyboardEvent(
    const MacOS *self, const NativeCode nativeCode,
    const comb::types::Modifiers modifiers, const bool isDown,
    const int64_t kSyntheticTag) -> void {
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

auto mac::util::isGroupExitTriggered(const MacOS *self) -> bool {
    if (!self->isHRMMode()) {
        return false;
    }

    const auto exitKey{self->getConfig().exitKey};
    const auto nativeCode{self->getCurrentNativeCode()};

    // TODO Only works if exitKey is a key
    return self->nativeCodeToKey(nativeCode) == self->getConfig().exitKey;
}

auto mac::util::getGroupAction(const MacOS *self)
    -> const grp::types::Action & {
    const auto *currentGroup{self->getCurrentGroup()};

    const auto nativeCode{self->getCurrentNativeCode()};
    const auto key{self->nativeCodeToKey(nativeCode)};

    return self->getCurrentGroup()->getAction(key);
}

auto mac::util::isKeymapInProgress(const MacOS *self,
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

auto mac::util::processKeymapInProgress(MacOS *self, Event &event,
                                        const comb::Combination &combination)
    -> void {
    self->addToCurrentCombination(combination);

    event = nullptr;
}

auto mac::util::processFinishedKeymap(MacOS *self, Event &event,
                                      const comb::Combination &combination)
    -> void {
    if (combination.containsMultipleRegulars()) {
        processMultipleRegularsBinding(self, combination);

        event = nullptr;
        return;
    }

    if (combination.containsNoModifiers()) {
        if (combination.isEmpty()) {
            mac::util::processEmptyBinding(self, event, combination);
        } else {
            mac::util::processNoModifiersBinding(self, event, combination);
        }
    }
}

auto mac::util::processNoModifiersBinding(MacOS *self, Event &event,
                                          const comb::Combination &binding)
    -> void {
    self->addToCurrentCombination(binding);
    self->setEventToCombination(event, self->getCurrentCombination());
    self->toggleLeaderUpProcessed();
    self->exitToGlobalGroup();
}

auto mac::util::processEmptyBinding(MacOS *self, Event &event,
                                    const comb::Combination &binding) -> void {
    const auto nativeCodeCombination{
        createCombinationFromNativeCode(self, self->getCurrentNativeCode())};

    self->addToCurrentCombination(nativeCodeCombination);

    self->setEventToCombination(event, self->getCurrentCombination());
    self->toggleLeaderUpProcessed();
    self->exitToGlobalGroup();
}

auto mac::util::sendMultipleRegulars(MacOS *self,
                                     const comb::Combination &combination)
    -> void {
    const auto [regularsArray, regularsCount]{combination.getRegulars()};
    const auto modifiers{combination.getModifiers()};

    for (size_t i{0}; i != regularsCount; ++i) {
        const auto regular{regularsArray.at(i)};
        const auto nativeCode{self->keyToNativeCode(regular)};

        createAndPostKeyboardEvent(self, nativeCode, modifiers, true,
                                   mac::util::kSyntheticTag);
        createAndPostKeyboardEvent(self, nativeCode, modifiers, false,
                                   mac::util::kSyntheticTag);
    }
}

auto mac::util::processMultipleRegularsBinding(
    MacOS *self, const comb::Combination &combination) -> void {
    sendMultipleRegulars(self, combination);

    self->toggleLeaderUpProcessed();
    self->exitToGlobalGroup();
}

[[nodiscard]] auto mac::util::isProcessingLeaderUp(const MacOS *self) -> bool {
    if (self->isLeaderUpProcessed()) {
        return false;
    }

    if (!self->isHRMMode()) {
        return false;
    }

    const auto *currentGroup{self->getCurrentGroup()};
    const auto nativeCode{self->getCurrentNativeCode()};

    return currentGroup->getLeader() == self->nativeCodeToKey(nativeCode);
}

auto mac::util::processSingleCombinationBinding(
    MacOS *self, Event &event, const grp::types::Combinations &binding)
    -> void {
    const auto combination{binding.combinations.at(0)};

    if (isKeymapInProgress(self, combination)) {
        std::cout << "keymap in progress\n";
        processKeymapInProgress(self, event, combination);
    }

    if (isKeymapFinished(self, combination)) {
        std::cout << "keymap finished\n";
        processFinishedKeymap(self, event, combination);
    }
}

auto mac::util::processMultipleCombinationsBinding(
    MacOS *self, Event &event, const grp::types::Combinations &binding)
    -> void {
    const auto combinationsInBinding{binding.count};

    for (size_t i{0}; i != combinationsInBinding; ++i) {
        const auto combination{binding.combinations.at(i)};

        sendMultipleRegulars(self, combination);
    }

    event = nullptr;
}

auto mac::util::processKeyPress(CGEventTapProxy proxy, CGEventType type,
                                CGEventRef event, void *refcon) -> CGEventRef {
    if (isSyntheticEvent(event)) {
        return event;
    }

    auto *self{static_cast<MacOS *>(refcon)};

    self->setCurrentNativeCode(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));

    // TODO only needed if leader is a modifier
    if (isProcessingLeaderUp(self)) {
        std::cout << "processing leader up\n";
        self->toggleLeaderUpProcessed();

        return nullptr;
    }

    if (isGroupExitTriggered(self)) {
        std::cout << "exiting hrm mode\n";
        self->exitToGlobalGroup();

        return nullptr;
    }

    const auto &groupAction{getGroupAction(self)};

    if (groupAction.isEmpty()) {
        mac::util::processEmptyBinding(self, event, {});

        return event;
    }

    if (groupAction.isSubgroup()) {
        std::cout << "entering group\n";

        self->enterGroup(groupAction.getSubgroup());

        return nullptr;
    }

    if (groupAction.isBinding()) {
        std::cout << "getting binding\n";

        const auto combinations{groupAction.getBinding()};

        if (combinations.count == 1) {
            processSingleCombinationBinding(self, event, combinations);
        } else {
            processMultipleCombinationsBinding(self, event, combinations);
        }
    }

    return event;
}
