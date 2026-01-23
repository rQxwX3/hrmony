#ifndef INPUT_TRANSFORM_HPP
#define INPUT_TRANSFORM_HPP

#include <keys.hpp>
#include <macos.hpp>

namespace mac::input::transform {
using key::Keys;
using mac::MacOS, mac::types::Event, mac::types::NativeModifier;

auto eventFlagsToModifiers(const MacOS *self, Event &event,
                           comb::types::Modifiers modifiers) -> void;

auto eventToCombination(const MacOS *self, Event &event,
                        const comb::Combination &combination) -> void;

auto eventToFields(const MacOS *self, Event &event, NativeCode nativeCode,
                   comb::types::Modifiers modifiers, bool isDown,
                   int64_t kSyntheticTag) -> void;
} // namespace mac::input::transform
#endif // INPUT_TRANSFORM_HPP
