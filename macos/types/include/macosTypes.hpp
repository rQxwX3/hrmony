#ifndef MACOS_TYPES_HPP
#define MACOS_TYPES_HPP

#include <keys.hpp>

#include <ApplicationServices/ApplicationServices.h>
#include <array>

namespace macOS::types {
using NativeModifier = CGEventFlags;
using NativeKeyCode = CGKeyCode;
using Event = CGEventRef;
constexpr size_t maxKeyCode{128};

using NativeCodeToModifierArray =
    std::array<key::Modifiers, static_cast<size_t>(key::Modifiers::m_size)>;

class NativeCodeToModifier {
  private:
    NativeCodeToModifierArray m_array;

  public:
    constexpr NativeCodeToModifier(const NativeCodeToModifierArray &array)
        : m_array{array} {}

  public:
    [[nodiscard]] auto at(NativeModifier nativeModifier) const
        -> key::Modifiers;
};

using ModifierToCGEventFlagsArray =
    std::array<CGEventFlags, static_cast<size_t>(key::Modifiers::m_size)>;

class ModifierToCGEventFlags {
  private:
    ModifierToCGEventFlagsArray m_array;

  public:
    constexpr ModifierToCGEventFlags(const ModifierToCGEventFlagsArray &array)
        : m_array{array} {}

  public:
    [[nodiscard]] auto at(key::Modifiers modifier) const -> CGEventFlags;
};
} // namespace macOS::types

#endif // MACOS_TYPES_HPP
