#ifndef MACOS_TYPES_HPP
#define MACOS_TYPES_HPP

#include <indexmap.hpp>
#include <keys.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace mac::types {
using NativeModifier = CGEventFlags;
using NativeCode = CGKeyCode;
using Event = CGEventRef;

constexpr size_t maxKeyCode{128};

using ModifierToCGEventFlagsType =
    hrm::IndexMap<key::Keys, CGEventFlags, key::modifiersCount,
                  [](key::Keys modifier) -> size_t {
                      return static_cast<size_t>(modifier) -
                             key::modifiersEnumOffset;
                  }>;
} // namespace mac::types

#endif // MACOS_TYPES_HPP
