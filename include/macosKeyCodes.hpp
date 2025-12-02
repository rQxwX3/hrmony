#ifndef MACOS_KEY_CODES
#define MACOS_KEY_CODES

#include "key.hpp"
#include "types.hpp"

#include <ApplicationServices/ApplicationServices.h>

namespace MacOSKeyCodes {

constexpr auto createNative2KeyMap() -> Native2KeyMap {
    Native2KeyMap arr{};

    arr[0] = Key::A;
    arr[1] = Key::S;
    arr[2] = Key::D;
    arr[3] = Key::F;
    arr[4] = Key::H;

    return arr;
};

constexpr auto createKey2NativeMap() -> Key2NativeMap {
    Key2NativeMap arr{};

    arr[static_cast<size_t>(Key::A)] = static_cast<NativeKeyCode>(0);
    arr[static_cast<size_t>(Key::S)] = static_cast<NativeKeyCode>(1);
    arr[static_cast<size_t>(Key::D)] = static_cast<NativeKeyCode>(2);
    arr[static_cast<size_t>(Key::F)] = static_cast<NativeKeyCode>(3);
    arr[static_cast<size_t>(Key::H)] = static_cast<NativeKeyCode>(4);

    return arr;
}

constexpr Native2KeyMap native2Key{createNative2KeyMap()};
constexpr Key2NativeMap key2Native{createKey2NativeMap()};
} // namespace MacOSKeyCodes

#endif // MACOS_KEY_CODES
