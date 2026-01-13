#include <platformTypes.hpp>

#ifdef __APPLE__
#include <macosTypes.hpp>
using mac::types::NativeCode, mac::types::NativeModifier,
    mac::types::maxKeyCode, mac::types::Event;
#endif // __APPLE__

#include <optional>

[[nodiscard]] auto plat::types::NativeCodeToKey::at(NativeCode nativeCode) const
    -> std::optional<key::Keys> {
    const auto index{static_cast<size_t>(nativeCode)};

    if (index > m_array.size() || index < 0) {
        return {};
    }

    return m_array.at(static_cast<size_t>(nativeCode));
}

[[nodiscard]] auto plat::types::KeyToNativeCode::at(key::Keys key) const
    -> NativeCode {
    return m_array.at(static_cast<size_t>(key));
}
