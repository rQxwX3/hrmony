#include <keys.hpp>
#include <types.hpp>

[[nodiscard]] auto NativeCodeToKey::at(NativeKeyCode nativeKey) const
    -> key::Keys {
    return m_array.at(static_cast<size_t>(nativeKey));
}

[[nodiscard]] auto KeyToNativeCode::at(key::Keys key) const -> NativeKeyCode {
    return m_array.at(static_cast<size_t>(key));
}

[[nodiscard]] auto ModifierToNativeCode::at(key::Modifiers modifier) const
    -> NativeKeyCode {
    return m_array.at(static_cast<size_t>(modifier));
}
