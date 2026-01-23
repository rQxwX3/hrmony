#ifndef INPUT_PROCESS_HPP
#define INPUT_PROCESS_HPP

#include <keys.hpp>
#include <macos.hpp>

namespace mac::input::process {
using key::Keys;
using mac::MacOS, mac::types::Event, mac::types::NativeModifier;

auto keymapInProgress(MacOS *self, Event &event,
                      const comb::Combination &combination) -> void;

auto finishedKeymap(MacOS *self, Event &event,
                    const comb::Combination &combination) -> void;

auto noModifiersBinding(MacOS *self, Event &event,
                        const comb::Combination &binding) -> void;

auto multipleRegularsBinding(MacOS *self, const comb::Combination &combination)
    -> void;

auto singleCombinationBinding(MacOS *self, Event &event,
                              const grp::types::Combinations &binding) -> void;

auto multipleCombinationsBinding(MacOS *self, Event &event,
                                 const grp::types::Combinations &binding)
    -> void;

auto emptyAction(MacOS *self, Event &event) -> void;

auto subgroupAction(MacOS *self, const grp::types::Action &action);

auto bindingAction(MacOS *self, const grp::types::Action &action, Event &event);

auto keyPress(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
              void *refcon) -> CGEventRef;
} // namespace mac::input::process
#endif // INPUT_PROCESS_HPP
