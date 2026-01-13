#include <keys.hpp>
#include <macosTypes.hpp>

#include <optional>

[[nodiscard]] auto
mac::types::ModifierToCGEventFlags::at(key::Keys modifier) const
    -> std::optional<CGEventFlags> {
    const auto index{static_cast<size_t>(modifier) - key::modifiersEnumOffset};

    if (index > m_array.size() || index < 0) {
        return {};
    }

    return m_array.at(index);
}
