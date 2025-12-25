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

using CombinationModifiers = std::array<Keys::Modifiers, maxKeymapModifiers>;
using CombinationKeys = std::array<Keys::Printables, maxKeymapKeys>;

class NativeKeyToPrintable {
    using Array = std::array<Keys::Printables, maxKeyCode>;

  private:
    Array m_array;

  public:
    constexpr NativeKeyToPrintable(const Array &array) : m_array{array} {}

  public:
    [[nodiscard]] auto at(NativeKeyCode nativeKey) const -> Keys::Printables;
};

class PrintableToNativeKey {
    using Array = std::array<NativeKeyCode,
                             static_cast<size_t>(Keys::Printables::m_size)>;

  private:
    Array m_array;

  public:
    constexpr PrintableToNativeKey(const Array &array) : m_array{array} {}

  public:
    [[nodiscard]] auto at(Keys::Printables key) const -> NativeKeyCode;
};

class ModifierToNativeModifier {
    using Array = std::array<NativeModifier,
                             static_cast<size_t>(Keys::Modifiers::m_size)>;

  private:
    Array m_array;

  public:
    constexpr ModifierToNativeModifier(const Array &array) : m_array{array} {}

  public:
    [[nodiscard]] auto at(Keys::Modifiers modifier) const -> NativeModifier;
};

using NativeKey2PrintableArray = std::array<Keys::Printables, maxKeyCode>;

using Printable2NativeKeyArray =
    std::array<NativeKeyCode, static_cast<size_t>(Keys::Printables::m_size)>;

using Modifier2NativeModifierArray =
    std::array<NativeModifier, static_cast<size_t>(Keys::Modifiers::m_size)>;

using KeyBindingArray =
    std::array<Combination, static_cast<size_t>(Keys::Printables::m_size)>;

#endif // TYPES_HPP
