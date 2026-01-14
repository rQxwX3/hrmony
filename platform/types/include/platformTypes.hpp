#ifndef PLATFORM_TYPES_HPP
#define PLATFORM_TYPES_HPP

#include <indexmap.hpp>
#include <keys.hpp>

#ifdef __APPLE__
#include <macosTypes.hpp>
using mac::types::NativeCode, mac::types::NativeModifier,
    mac::types::maxKeyCode, mac::types::Event;
#endif // __APPLE__

namespace plt::types {
using NativeCodeToKeyType =
    hrm::IndexMap<NativeCode, key::Keys, maxKeyCode,
                  [](NativeCode nativeCode) -> size_t {
                      return static_cast<size_t>(nativeCode);
                  }>;

NativeCodeToKeyType NativeCodeToKey{};

using KeyToNativeCodeType =
    hrm::IndexMap<key::Keys, NativeCode, key::keysCount,
                  [](key::Keys key) -> size_t {
                      if (key::isModifier(key)) {
                          return static_cast<size_t>(key) - 1;
                      }

                      return static_cast<size_t>(key);
                  }>;

KeyToNativeCodeType KeyToNativeCode{};

} // namespace plt::types

#endif // PLATFORM_TYPES_HPP
