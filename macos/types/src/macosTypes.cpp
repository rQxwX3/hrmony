#include <macosTypes.hpp>

[[nodiscard]] auto
macOS::types::ModifierToCGEventFlags::at(key::Modifiers modifier) const
    -> CGEventFlags {
    return m_array.at(static_cast<size_t>(modifier));
}
