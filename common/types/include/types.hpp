#ifndef TYPES_HPP
#define TYPES_HPP

#include <array>
#include <keys.hpp>

#ifdef __APPLE__
#include <macosTypes.hpp>
using macOS::types::NativeCode, macOS::types::NativeModifier,
    macOS::types::maxKeyCode, macOS::types::Event;
#endif // __APPLE__

class Combination;

constexpr size_t maxKeymapModifiers{4};
constexpr size_t maxKeymapRegulars{4};

using CombinationModifiers = std::array<key::Keys, maxKeymapModifiers>;
using CombinationRegulars = std::array<key::Keys, maxKeymapRegulars>;

using NativeCodeToKeyArray = std::array<key::Keys, maxKeyCode>;

using ModifierToNativeCodeArray =
    std::array<NativeModifier, static_cast<size_t>(key::Modifiers::m_size)>;

using KeyToNativeCodeArray =
    std::array<NativeCode, static_cast<size_t>(key::Keys::m_size)>;

using KeyBindingArray =
    std::array<Combination, static_cast<size_t>(key::Keys::m_size)>;

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

class ModifierToNativeCode {
  private:
    ModifierToNativeCodeArray m_array;

  public:
    constexpr ModifierToNativeCode(const ModifierToNativeCodeArray &array)
        : m_array{array} {}

  public:
    [[nodiscard]] auto at(key::Modifiers modifier) const -> NativeCode;
};

#endif // TYPES_HPP
