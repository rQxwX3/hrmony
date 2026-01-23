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

namespace process = mac::input::process;
namespace is = mac::input::validate;
namespace set = mac::input::transform;
namespace send = mac::input::dispatch;

auto keymapInProgress(MacOS *self, Event &event,
                      const comb::Combination &combination) -> void {
    self->addToCurrentCombination(combination);

    event = nullptr;
}

auto noModifiersBinding(MacOS *self, Event &event,
                        const comb::Combination &binding) -> void {
    self->addToCurrentCombination(binding);
    set::eventToCombination(self, event, self->getCurrentCombination());
    self->toggleLeaderUpProcessed();
    self->exitToGlobalGroup();
}

auto emptyBinding(MacOS *self, Event &event, const comb::Combination &binding)
    -> void {
    const auto key{self->nativeCodeToKey(self->getCurrentNativeCode())};

    if (!key.has_value()) {
        // TODO
    }

    const auto nativeCodeCombination{
        comb::Combination({.array = {key.value()}, .count = 1})};

    self->addToCurrentCombination(nativeCodeCombination);

    set::eventToCombination(self, event, self->getCurrentCombination());

    self->toggleLeaderUpProcessed();
    self->exitToGlobalGroup();
}

auto multipleRegularsBinding(MacOS *self, const comb::Combination &combination)
    -> void {
    send::containingRegulars(self, combination);

    self->toggleLeaderUpProcessed();
    self->exitToGlobalGroup();
}

auto finishedKeymap(MacOS *self, Event &event,
                    const comb::Combination &combination) -> void {
    if (combination.containsMultipleRegulars()) {
        process::multipleRegularsBinding(self, combination);

        event = nullptr;
        return;
    }

    if (combination.containsNoModifiers()) {
        if (combination.isEmpty()) {
            process::emptyBinding(self, event, combination);
        } else {
            process::noModifiersBinding(self, event, combination);
        }
    }
}

auto singleCombinationBinding(MacOS *self, Event &event,
                              const grp::types::Combinations &binding) -> void {
    const auto combination{binding.combinations.at(0)};

    if (is::keymapInProgress(self, combination)) {
        std::cout << "keymap in progress\n";
        process::keymapInProgress(self, event, combination);
    }

    if (is::keymapFinished(self, combination)) {
        std::cout << "keymap finished\n";
        process::finishedKeymap(self, event, combination);
    }
}

auto multipleCombinationsBinding(MacOS *self, Event &event,
                                 const grp::types::Combinations &binding)
    -> void {
    const auto combinationsInBinding{binding.count};

    for (size_t i{0}; i != combinationsInBinding; ++i) {
        const auto combination{binding.combinations.at(i)};

        send::containingRegulars(self, combination);
    }

    event = nullptr;
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
        process::emptyBinding(self, event, {});

        return event;
    }

    if (groupAction.isSubgroup()) {
        std::cout << "entering group\n";

        const auto subgroup{groupAction.getSubgroup()};

        if (!subgroup.has_value()) {
            // TODO
        }

        self->enterGroup(*groupAction.getSubgroup());

        return nullptr;
    }

    if (groupAction.isBinding()) {
        const auto combinations{groupAction.getBinding()};

        if (!combinations.has_value()) {
            // TODO
        }

        if (combinations->count == 1) {
            process::singleCombinationBinding(self, event,
                                              combinations.value());
        } else {
            process::multipleCombinationsBinding(self, event,
                                                 combinations.value());
        }
    }

    return event;
}
} // namespace mac::input::process
