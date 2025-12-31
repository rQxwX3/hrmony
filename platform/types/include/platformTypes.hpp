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
    std::array<NativeCode, key::keysCount> m_array;

  public:
    [[nodiscard]] auto at(key::Keys key) const -> NativeCode;

    constexpr auto operator[](key::Keys key) -> NativeCode & {
        if (key::isModifier(key)) {
            // Subtracting 1 is required because of Keys::m_regularsCount
            return m_array.at(static_cast<size_t>(key) - 1);
        }

        return m_array.at(static_cast<size_t>(key));
    }
};
} // namespace plat::types

#endif // PLATFORM_TYPES_HPP
