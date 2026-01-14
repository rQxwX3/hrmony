#ifndef MACOS_CONSTANTS_HPP
#define MACOS_CONSTANTS_HPP

#include <keys.hpp>
#include <macosTypes.hpp>
#include <platformTypes.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace mac::consts {
constexpr auto createNativeCodeToKey() -> void {
    using ::key::Keys, plat::types::NativeCodeToKey;

    NativeCodeToKey[0] = Keys::A;
    NativeCodeToKey[1] = Keys::S;
    NativeCodeToKey[2] = Keys::D;
    NativeCodeToKey[3] = Keys::F;
    NativeCodeToKey[4] = Keys::H;
    NativeCodeToKey[9] = Keys::V;
    NativeCodeToKey[12] = Keys::Q;
    NativeCodeToKey[13] = Keys::W;
    NativeCodeToKey[17] = Keys::T;
    NativeCodeToKey[37] = Keys::L;
    NativeCodeToKey[34] = Keys::I;
    NativeCodeToKey[38] = Keys::J;
    NativeCodeToKey[40] = Keys::K;
    NativeCodeToKey[41] = Keys::SEMICOLON;

    NativeCodeToKey[54] = Keys::RIGHT_CMD;
    NativeCodeToKey[55] = Keys::LEFT_CMD;
    NativeCodeToKey[59] = Keys::LEFT_CTRL;
    NativeCodeToKey[60] = Keys::LEFT_SHIFT;
    NativeCodeToKey[58] = Keys::RIGHT_ALT;
};

// constexpr plat::types::NativeCodeToKey
// nativeCodeToKey{createNativeCodeToKey()};

constexpr auto createKeyToNativeCode() -> plat::types::KeyToNativeCode {
    plat::types::KeyToNativeCode keyToNativeCode{};

    using ::key::Keys;

    keyToNativeCode[Keys::A] = 0;
    keyToNativeCode[Keys::S] = 1;
    keyToNativeCode[Keys::H] = 4;
    keyToNativeCode[Keys::V] = 9;
    keyToNativeCode[Keys::W] = 13;
    keyToNativeCode[Keys::T] = 17;
    keyToNativeCode[Keys::W] = 13;
    keyToNativeCode[Keys::I] = 34;
    keyToNativeCode[Keys::J] = 38;
    keyToNativeCode[Keys::K] = 40;

    keyToNativeCode[Keys::RIGHT_CMD] = 55;
    keyToNativeCode[Keys::LEFT_CTRL] = 59;
    keyToNativeCode[Keys::LEFT_SHIFT] = 60;
    keyToNativeCode[Keys::RIGHT_ALT] = 58;

    return keyToNativeCode;
}

constexpr plat::types::KeyToNativeCode keyToNativeCode{createKeyToNativeCode()};

using mac::types::ModifierToCGEventFlags;

constexpr auto createModifierToCGEventFlags() -> ModifierToCGEventFlags {
    ModifierToCGEventFlags modifierToCGEventFlags{};

    using ::key::Keys;

    modifierToCGEventFlags[Keys::RIGHT_CMD] = kCGEventFlagMaskCommand;
    modifierToCGEventFlags[Keys::LEFT_CTRL] = kCGEventFlagMaskControl;
    modifierToCGEventFlags[Keys::LEFT_SHIFT] = kCGEventFlagMaskShift;
    modifierToCGEventFlags[Keys::RIGHT_ALT] = kCGEventFlagMaskAlternate;

    return modifierToCGEventFlags;
}

constexpr ModifierToCGEventFlags modifierToCGEventFlags{
    createModifierToCGEventFlags()};
} // namespace mac::consts

#endif // MACOS_CONSTANTS_HPP
