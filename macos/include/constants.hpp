#ifndef MACOS_CONSTANTS_HPP
#define MACOS_CONSTANTS_HPP

#include <keys.hpp>
#include <macosTypes.hpp>
#include <platformTypes.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace mac::consts {
using ::key::Keys;
using mac::types::ModifierToCGEventFlags;
using plt::types::NativeCodeToKey, plt::types::KeyToNativeCode;

constexpr auto createNativeCodeToKey() -> NativeCodeToKey {
    NativeCodeToKey nativeCodeToKey;

    nativeCodeToKey[0] = Keys::A;
    nativeCodeToKey[1] = Keys::S;
    nativeCodeToKey[2] = Keys::D;
    nativeCodeToKey[3] = Keys::F;
    nativeCodeToKey[4] = Keys::H;
    nativeCodeToKey[9] = Keys::V;
    nativeCodeToKey[12] = Keys::Q;
    nativeCodeToKey[13] = Keys::W;
    nativeCodeToKey[17] = Keys::T;
    nativeCodeToKey[37] = Keys::L;
    nativeCodeToKey[34] = Keys::I;
    nativeCodeToKey[38] = Keys::J;
    nativeCodeToKey[40] = Keys::K;
    nativeCodeToKey[41] = Keys::SEMICOLON;

    nativeCodeToKey[54] = Keys::RIGHT_CMD;
    nativeCodeToKey[55] = Keys::LEFT_CMD;
    nativeCodeToKey[59] = Keys::LEFT_CTRL;
    nativeCodeToKey[60] = Keys::LEFT_SHIFT;
    nativeCodeToKey[58] = Keys::RIGHT_ALT;

    return nativeCodeToKey;
};

constexpr auto createKeyToNativeCode() -> KeyToNativeCode {
    KeyToNativeCode keyToNativeCode;

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

constexpr auto createModifierToCGEventFlags() -> ModifierToCGEventFlags {
    ModifierToCGEventFlags modifierToCGEventFlags;

    modifierToCGEventFlags[Keys::RIGHT_CMD] = kCGEventFlagMaskCommand;
    modifierToCGEventFlags[Keys::LEFT_CTRL] = kCGEventFlagMaskControl;
    modifierToCGEventFlags[Keys::LEFT_SHIFT] = kCGEventFlagMaskShift;
    modifierToCGEventFlags[Keys::RIGHT_ALT] = kCGEventFlagMaskAlternate;

    return modifierToCGEventFlags;
}
} // namespace mac::consts

#endif // MACOS_CONSTANTS_HPP
