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
    const auto combinationType{combination.getType()};

    switch (combinationType) {
        using Type = comb::Combination::Type;

    case Type::SINGLE_REGULAR:
        process::singleRegularCombination(self, event, combination);
        break;

    case Type::MULTIPLE_REGULARS:
        process::multipleRegularsCombination(self, event, combination);
        break;

    case Type::EMPTY:
        process::emptyAction(self, event);
    }
}

auto singleRegularCombination(MacOS *self, Event &event,
                              const comb::Combination &combination) -> void {
    self->addToCurrentCombination(combination);
    set::eventToSingleRegularCombination(self, event,
                                         self->getCurrentCombination());
    self->resetCurrentGroup();
}

auto multipleRegularsCombination(MacOS *self, Event &event,
                                 const comb::Combination &combination) -> void {
    send::multipleRegulars(self, combination);

    self->resetCurrentGroup();

    event = nullptr;
}

auto singleCombinationBinding(MacOS *self, Event &event,
                              const grp::types::Combinations &binding) -> void {
    const auto combination{binding.array.at(0)};

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
        const auto combination{binding.array.at(i)};

        send::multipleRegulars(self, combination);
    }

    event = nullptr;
}

auto emptyAction(MacOS *self, Event &event) -> void {
    const auto key{self->getCurrentKey()};

    const auto nativeCodeCombination{
        comb::Combination({.array = {key}, .count = 1})};

    self->addToCurrentCombination(nativeCodeCombination);

    const auto currentCombination{self->getCurrentCombination()};

    if (currentCombination.containsMultipleRegulars()) {
        // TODO
        return;
    }

    set::eventToSingleRegularCombination(self, event,
                                         self->getCurrentCombination());

    self->resetCurrentGroup();
}

auto subgroupAction(MacOS *self, Event &event, const grp::types::Action &action)
    -> void {
    const auto subgroup{action.getSubgroup()};

    if (!subgroup.has_value()) {
        // TODO
    }

    if (subgroup.value()->isGlobalSubgroup()) {
        const auto leaderUpToBeProcessed{self->getLeaderUpToBeProcessed()};

        if (key::Keys::NULLKEY == leaderUpToBeProcessed) {
            self->setLeaderUpToBeProcessed(subgroup.value()->getLeader());
            return;
        }

        if (self->getCurrentKey() != leaderUpToBeProcessed) {
            return;
        }
    }

    std::cout << "entering group\n";
    self->setCurrentGroup(subgroup.value());
    event = nullptr;
}

auto bindingAction(MacOS *self, Event &event, const grp::types::Action &action)
    -> void {
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

auto exitAction(MacOS *self, Event &event) -> void {
    std::cout << "exiting to global group\n";

    self->resetCurrentGroup();

    event = nullptr;
}

auto groupActions(MacOS *self, Event &event) -> void {
    const auto &action(self->getGroupAction());
    const auto actionType{action.getType()};

    switch (actionType) {
        using Type = grp::types::Action::Type;

    case Type::BINDING:
        process::bindingAction(self, event, action);
        break;

    case Type::SUBGROUP:
        process::subgroupAction(self, event, action);
        break;

    case Type::EXIT:
        process::exitAction(self, event);
        break;

    case Type::EMPTY:
        process::emptyAction(self, event);
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

    process::groupActions(self, event);
    return event;
}
} // namespace mac::input::process
