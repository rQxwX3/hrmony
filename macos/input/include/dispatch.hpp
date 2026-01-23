#ifndef INPUT_DISPATCH_HPP
#define INPUT_DISPATCH_HPP

#include <keys.hpp>
#include <macos.hpp>

namespace mac::input::dispatch {
using key::Keys;
using mac::MacOS, mac::types::Event, mac::types::NativeModifier;

auto multipleRegulars(MacOS *self, const comb::Combination &combination)
    -> void;
} // namespace mac::input::dispatch

#endif // INPUT_DISPATCH_HPP
