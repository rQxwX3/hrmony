#ifndef TYPES_HPP
#define TYPES_HPP

#include <array>
#include <keys.hpp>

#ifdef __APPLE__
#include <macosTypes.hpp>
#endif // __APPLE__

class Combination;

constexpr size_t maxKeymapModifiers{4};
constexpr size_t maxKeymapKeys{4};

using CombinationModifiers = std::array<key::Modifiers, maxKeymapModifiers>;
using CombinationKeys = std::array<key::Keys, maxKeymapKeys>;

using NativeKeyToPrintableArray = std::array<key::Keys, maxKeyCode>;

using PrintableToNativeKeyArray =
    std::array<NativeKeyCode, static_cast<size_t>(key::Keys::m_size)>;

using ModifierToNativeModifierArray =
    std::array<NativeModifier, static_cast<size_t>(key::Modifiers::m_size)>;

using KeyBindingArray =
    std::array<Combination, static_cast<size_t>(key::Keys::m_size)>;

class NativeKeyToPrintable {
  private:
    NativeKeyToPrintableArray m_array;

  public:
    constexpr NativeKeyToPrintable(const NativeKeyToPrintableArray &array)
        : m_array{array} {}

  public:
    [[nodiscard]] auto at(NativeKeyCode nativeKey) const -> key::Keys;
};

class PrintableToNativeKey {
  private:
    PrintableToNativeKeyArray m_array;

  public:
    constexpr PrintableToNativeKey(const PrintableToNativeKeyArray &array)
        : m_array{array} {}

  public:
    [[nodiscard]] auto at(key::Keys key) const -> NativeKeyCode;
};

class ModifierToNativeModifier {
  private:
    ModifierToNativeModifierArray m_array;

  public:
    constexpr ModifierToNativeModifier(
        const ModifierToNativeModifierArray &array)
        : m_array{array} {}

  public:
    [[nodiscard]] auto at(key::Modifiers modifier) const -> NativeModifier;
};

#endif // TYPES_HPP
