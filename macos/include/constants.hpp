#ifndef MACOS_CONSTANTS_HPP
#define MACOS_CONSTANTS_HPP

#include <keys.hpp>
#include <macosTypes.hpp>
#include <platformTypes.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace mac::consts {
using ::key::Keys;
using mac::types::ModifierToCGEventFlagsType;
using plt::types::NativeCodeToKeyType, plt::types::KeyToNativeCodeType;

constexpr auto createNativeCodeToKey() -> NativeCodeToKeyType {
    NativeCodeToKeyType NativeCodeToKey;

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

    return NativeCodeToKey;
};

constexpr auto createKeyToNativeCode() -> KeyToNativeCodeType {
    KeyToNativeCodeType KeyToNativeCode;

    KeyToNativeCode[Keys::A] = 0;
    KeyToNativeCode[Keys::S] = 1;
    KeyToNativeCode[Keys::H] = 4;
    KeyToNativeCode[Keys::V] = 9;
    KeyToNativeCode[Keys::W] = 13;
    KeyToNativeCode[Keys::T] = 17;
    KeyToNativeCode[Keys::W] = 13;
    KeyToNativeCode[Keys::I] = 34;
    KeyToNativeCode[Keys::J] = 38;
    KeyToNativeCode[Keys::K] = 40;

    KeyToNativeCode[Keys::RIGHT_CMD] = 55;
    KeyToNativeCode[Keys::LEFT_CTRL] = 59;
    KeyToNativeCode[Keys::LEFT_SHIFT] = 60;
    KeyToNativeCode[Keys::RIGHT_ALT] = 58;

    return KeyToNativeCode;
}

constexpr auto createModifierToCGEventFlags() -> ModifierToCGEventFlagsType {
    ModifierToCGEventFlagsType ModifierToCGEventFlags;

    ModifierToCGEventFlags[Keys::RIGHT_CMD] = kCGEventFlagMaskCommand;
    ModifierToCGEventFlags[Keys::LEFT_CTRL] = kCGEventFlagMaskControl;
    ModifierToCGEventFlags[Keys::LEFT_SHIFT] = kCGEventFlagMaskShift;
    ModifierToCGEventFlags[Keys::RIGHT_ALT] = kCGEventFlagMaskAlternate;

    return ModifierToCGEventFlags;
}
} // namespace mac::consts

#endif // MACOS_CONSTANTS_HPP
