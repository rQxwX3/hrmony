#ifndef MACOS_KEY_CODES
#define MACOS_KEY_CODES

#include "key.hpp"
#include "types.hpp"

#include <ApplicationServices/ApplicationServices.h>
#include <unordered_map>

namespace MacOSKeyCodes {
const std::unordered_map<NativeKeyCode, Key> native2Key{
    {static_cast<NativeKeyCode>(1), Key::A},
    {static_cast<NativeKeyCode>(11), Key::B},
};

const std::unordered_map<Key, NativeKeyCode> key2Native{
    {Key::A, static_cast<NativeKeyCode>(1)},
    {Key::B, static_cast<NativeKeyCode>(11)},
};
} // namespace MacOSKeyCodes

#endif // MACOS_KEY_CODES
