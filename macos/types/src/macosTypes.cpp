#include <keys.hpp>
#include <macosTypes.hpp>

[[nodiscard]] auto
mac::types::ModifierToCGEventFlags::at(key::Keys modifier) const
    -> CGEventFlags {
    return m_array.at(static_cast<size_t>(modifier) - key::modifiersEnumOffset);
}
