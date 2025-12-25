#include <keys.hpp>
#include <types.hpp>

[[nodiscard]] auto NativeKeyToPrintable::at(NativeKeyCode nativeKey) const
    -> Keys::Printables {
    return m_array.at(static_cast<size_t>(nativeKey));
}

[[nodiscard]] auto PrintableToNativeKey::at(Keys::Printables key) const
    -> NativeKeyCode {
    return m_array.at(static_cast<size_t>(key));
}

[[nodiscard]] auto ModifierToNativeModifier::at(Keys::Modifiers modifier) const
    -> NativeModifier {
    return m_array.at(static_cast<size_t>(modifier));
}
