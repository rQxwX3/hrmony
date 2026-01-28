#ifndef INPUT_PROCESS_HPP
#define INPUT_PROCESS_HPP

#include <keys.hpp>
#include <macos.hpp>

namespace mac::input::process {
using key::Keys;
using mac::MacOS, mac::types::Event, mac::types::NativeModifier;

auto inputInProgress(MacOS *self, Event &event,
                     const comb::Combination &combination) -> void;

auto finishedInput(MacOS *self, Event &event,
                   const comb::Combination &combination) -> void;

auto singleRegularCombination(MacOS *self, Event &event,
                              const comb::Combination &combination) -> void;

auto multipleRegularsCombination(MacOS *self, Event &event,
                                 const comb::Combination &combination) -> void;

auto singleCombinationBinding(MacOS *self, Event &event,
                              const grp::types::Combinations &binding) -> void;

auto multipleCombinationsBinding(MacOS *self, Event &event,
                                 const grp::types::Combinations &binding)
    -> void;

auto emptyAction(MacOS *self, Event &event) -> void;

auto subgroupAction(MacOS *self, Event &event, const grp::types::Action &action)
    -> void;

auto bindingAction(MacOS *self, Event &event, const grp::types::Action &action)
    -> void;

auto exitAction(MacOS *self, Event &event) -> void;

auto groupActions(MacOS *self, Event &event) -> void;

auto keyPress(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
              void *refcon) -> CGEventRef;
} // namespace mac::input::process
#endif // INPUT_PROCESS_HPP
