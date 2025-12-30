#include <platformTypes.hpp>

#ifdef __APPLE__
#include <macosTypes.hpp>
using mac::types::NativeCode, mac::types::NativeModifier,
    mac::types::maxKeyCode, mac::types::Event;
#endif // __APPLE__

[[nodiscard]] auto plat::types::NativeCodeToKey::at(NativeCode nativeCode) const
    -> key::Keys {
    return m_array.at(static_cast<size_t>(nativeCode));
}

[[nodiscard]] auto plat::types::KeyToNativeCode::at(key::Keys key) const
    -> NativeCode {
    return m_array.at(static_cast<size_t>(key));
}
