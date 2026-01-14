#include <platformTypes.hpp>

#ifdef __APPLE__
#include <macosTypes.hpp>
using mac::types::NativeCode, mac::types::NativeModifier,
    mac::types::maxKeyCode, mac::types::Event;
#endif // __APPLE__

#include <optional>

// [[nodiscard]] auto plat::types::NativeCodeToKey::at(NativeCode nativeCode)
// const
//     -> std::optional<key::Keys> {
//     const auto index{static_cast<size_t>(nativeCode)};
//
//     if (index > m_array.size()) {
//         return {};
//     }
//
//     return m_array[index];
// }

[[nodiscard]] auto plat::types::KeyToNativeCode::at(key::Keys key) const
    -> std::optional<NativeCode> {
    const auto index{static_cast<size_t>(key)};

    if (index > m_array.size()) {
        return {};
    }

    return m_array[index];
}
