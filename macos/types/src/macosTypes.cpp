#include <constants.hpp>
#include <macosTypes.hpp>

#include <iostream>

[[nodiscard]] auto
macOS::types::ModifierToCGEventFlags::at(key::Modifiers modifier) const
    -> CGEventFlags {
    return m_array.at(static_cast<size_t>(modifier));
}

[[nodiscard]] auto
macOS::types::NativeCodeToModifier::at(NativeModifier nativeModifier) const
    -> key::Modifiers {

    if (nativeModifier < constants::modifierNativeCodeOffsetFromZero) {
        return key::Modifiers::NULLKEY;
    }

    return m_array.at(static_cast<size_t>(nativeModifier) -
                      constants::modifierNativeCodeOffsetFromZero);
}
