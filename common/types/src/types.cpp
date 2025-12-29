#include <keys.hpp>
#include <types.hpp>

[[nodiscard]] auto NativeCodeToKey::at(NativeCode nativeCode) const
    -> key::Keys {
    return m_array.at(static_cast<size_t>(nativeCode));
}

[[nodiscard]] auto KeyToNativeCode::at(key::Keys key) const -> NativeCode {
    return m_array.at(static_cast<size_t>(key));
}

[[nodiscard]] auto ModifierToNativeCode::at(key::Modifiers modifier) const
    -> NativeCode {
    return m_array.at(static_cast<size_t>(modifier));
}
