#ifndef PLATFORM_TYPES_HPP
#define PLATFORM_TYPES_HPP

#include <array>
#include <keys.hpp>

#ifdef __APPLE__
#include <macosTypes.hpp>
using mac::types::NativeCode, mac::types::NativeModifier,
    mac::types::maxKeyCode, mac::types::Event;
#endif // __APPLE__

namespace plat::types {
using NativeCodeToKeyArray = std::array<key::Keys, maxKeyCode>;
using KeyToNativeCodeArray = std::array<NativeCode, key::keysCount>;

class NativeCodeToKey {
  private:
    NativeCodeToKeyArray m_array;

  public:
    constexpr NativeCodeToKey(const NativeCodeToKeyArray &array)
        : m_array{array} {}

  public:
    [[nodiscard]] auto at(NativeCode nativeCode) const -> key::Keys;
};

class KeyToNativeCode {
  private:
    KeyToNativeCodeArray m_array;

  public:
    constexpr KeyToNativeCode(const KeyToNativeCodeArray &array)
        : m_array{array} {}

  public:
    [[nodiscard]] auto at(key::Keys key) const -> NativeCode;
};
} // namespace plat::types

#endif // PLATFORM_TYPES_HPP
