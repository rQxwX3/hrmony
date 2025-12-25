#include <keys.hpp>
#include <types.hpp>

[[nodiscard]] auto NativeKeyToPrintable::at(NativeKeyCode nativeKey) const
    -> key::Keys {
    return m_array.at(static_cast<size_t>(nativeKey));
}

[[nodiscard]] auto PrintableToNativeKey::at(key::Keys key) const
    -> NativeKeyCode {
    return m_array.at(static_cast<size_t>(key));
}

[[nodiscard]] auto ModifierToNativeModifier::at(key::Modifiers modifier) const
    -> NativeModifier {
    return m_array.at(static_cast<size_t>(modifier));
}
