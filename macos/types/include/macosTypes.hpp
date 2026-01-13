#ifndef MACOS_TYPES_HPP
#define MACOS_TYPES_HPP

#include <keys.hpp>

#include <ApplicationServices/ApplicationServices.h>
#include <array>
#include <optional>

namespace mac::types {
using NativeModifier = CGEventFlags;
using NativeCode = CGKeyCode;
using Event = CGEventRef;

constexpr size_t maxKeyCode{128};

class ModifierToCGEventFlags {
  private:
    std::array<CGEventFlags, static_cast<size_t>(key::modifiersCount)> m_array;

  public:
    constexpr auto operator[](key::Keys modifier) -> CGEventFlags & {
        return m_array.at(static_cast<size_t>(modifier) -
                          key::modifiersEnumOffset);
    }

    [[nodiscard]] auto at(key::Keys modifier) const
        -> std::optional<CGEventFlags>;
};

} // namespace mac::types

#endif // MACOS_TYPES_HPP
