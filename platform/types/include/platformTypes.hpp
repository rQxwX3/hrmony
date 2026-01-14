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
constexpr auto nativeCodeToKeyConverter{[](NativeCode nativeCode) -> size_t {
    return static_cast<size_t>(nativeCode);
}};

using NativeCodeToKeyType =
    hrm::IndexMap<NativeCode, key::Keys, maxKeyCode, nativeCodeToKeyConverter>;

NativeCodeToKeyType NativeCodeToKey{};

constexpr auto keyToNativeCodeConverter{[](key::Keys key) -> size_t {
    if (key::isModifier(key)) {
        return static_cast<size_t>(key) - 1;
    }

    return static_cast<size_t>(key);
}};

using KeyToNativeCodeType = hrm::IndexMap<key::Keys, NativeCode, key::keysCount,
                                          keyToNativeCodeConverter>;

KeyToNativeCodeType KeyToNativeCode{};

} // namespace plt::types

#endif // PLATFORM_TYPES_HPP
