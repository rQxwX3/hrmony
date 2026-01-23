#include <dispatch.hpp>
#include <keys.hpp>
#include <macos.hpp>
#include <process.hpp>
#include <transform.hpp>
#include <validate.hpp>

#include <iostream>

namespace mac::input::process {
using key::Keys;
using mac::MacOS, mac::types::Event, mac::types::NativeModifier;

namespace is = mac::input::validate;
namespace set = mac::input::transform;
namespace send = mac::input::dispatch;
namespace process = mac::input::process;

auto inputInProgress(MacOS *self, Event &event,
                     const comb::Combination &combination) -> void {
    self->addToCurrentCombination(combination);

    event = nullptr;
}

auto finishedInput(MacOS *self, Event &event,
                   const comb::Combination &combination) -> void {
    if (combination.isEmpty()) {
        process::emptyAction(self, event);
        return;
    }

    if (combination.containsMultipleRegulars()) {
        process::multipleRegularsBinding(self, event, combination);
    } else {
        process::singleRegularBinding(self, event, combination);
    }
}

auto singleRegularBinding(MacOS *self, Event &event,
                          const comb::Combination &binding) -> void {
    self->addToCurrentCombination(binding);
    set::eventToSingleRegularCombination(self, event,
                                         self->getCurrentCombination());
    self->toggleLeaderUpProcessed();
    self->exitToGlobalGroup();
}

auto multipleRegularsBinding(MacOS *self, Event &event,
                             const comb::Combination &combination) -> void {
    send::multipleRegulars(self, combination);

    self->toggleLeaderUpProcessed();
    self->exitToGlobalGroup();

    event = nullptr;
}

auto singleCombinationBinding(MacOS *self, Event &event,
                              const grp::types::Combinations &binding) -> void {
    const auto combination{binding.combinations.at(0)};

    if (is::inputInProgress(self, combination)) {
        std::cout << "keymap in progress\n";
        process::inputInProgress(self, event, combination);
    } else {
        std::cout << "keymap finished\n";
        process::finishedInput(self, event, combination);
    }
}

auto multipleCombinationsBinding(MacOS *self, Event &event,
                                 const grp::types::Combinations &binding)
    -> void {
    const auto combinationsInBinding{binding.count};

    for (size_t i{0}; i != combinationsInBinding; ++i) {
        const auto combination{binding.combinations.at(i)};

        send::multipleRegulars(self, combination);
    }

    event = nullptr;
}

auto emptyAction(MacOS *self, Event &event) -> void {
    const auto nativeCode{self->getCurrentNativeCode()};
    const auto key{self->nativeCodeToKey(nativeCode)};

    if (!key.has_value()) {
        // TODO
    }

    const auto nativeCodeCombination{
        comb::Combination({.array = {key.value()}, .count = 1})};

    self->addToCurrentCombination(nativeCodeCombination);

    const auto currentCombination{self->getCurrentCombination()};

    if (currentCombination.containsMultipleRegulars()) {
        // TODO
        return;
    }

    set::eventToSingleRegularCombination(self, event,
                                         self->getCurrentCombination());

    self->toggleLeaderUpProcessed();
    self->exitToGlobalGroup();
}

auto subgroupAction(MacOS *self, const grp::types::Action &action) {
    std::cout << "entering group\n";

    const auto subgroup{action.getSubgroup()};

    if (!subgroup.has_value()) {
        // TODO
    }

    self->enterGroup(subgroup.value());
}

auto bindingAction(MacOS *self, const grp::types::Action &action,
                   Event &event) {
    const auto combinations{action.getBinding()};

    if (!combinations.has_value()) {
        // TODO
    }

    if (1 == combinations->count) {
        process::singleCombinationBinding(self, event, combinations.value());
    } else {
        process::multipleCombinationsBinding(self, event, combinations.value());
    }
}

auto keyPress(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
              void *refcon) -> CGEventRef {
    if (is::syntheticEvent(event)) {
        return event;
    }

    auto *self{static_cast<MacOS *>(refcon)};

    self->setCurrentNativeCode(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));

    // TODO only needed if leader is a modifier
    if (is::processingLeaderUp(self)) {
        std::cout << "processing leader up\n";
        self->toggleLeaderUpProcessed();

        return nullptr;
    }

    if (is::groupExitTriggered(self)) {
        std::cout << "exiting hrm mode\n";
        self->exitToGlobalGroup();

        return nullptr;
    }

    const auto nativeCode{self->getCurrentNativeCode()};
    const auto key{self->nativeCodeToKey(nativeCode)};

    if (!key.has_value()) {
        // TODO
    }

    const auto *currentGroup{self->getCurrentGroup()};
    const auto &groupAction{currentGroup->getAction(key.value())};

    if (groupAction.isEmpty()) {
        process::emptyAction(self, event);

        return event;
    }

    if (groupAction.isSubgroup()) {
        process::subgroupAction(self, groupAction);

        return nullptr;
    }

    if (groupAction.isBinding()) {
        process::bindingAction(self, groupAction, event);
    }

    return event;
}
} // namespace mac::input::process
