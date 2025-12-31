#ifndef MACOS_CONSTANTS_HPP
#define MACOS_CONSTANTS_HPP

#include <keys.hpp>
#include <macosTypes.hpp>
#include <platformTypes.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace mac::consts {
constexpr auto createNativeCodeToKeyArray()
    -> plat::types::NativeCodeToKeyArray {
    plat::types::NativeCodeToKeyArray arr{};

    using ::key::Keys;

    arr[0] = Keys::A;
    arr[1] = Keys::S;
    arr[2] = Keys::D;
    arr[3] = Keys::F;
    arr[4] = Keys::H;
    arr[12] = Keys::Q;
    arr[13] = Keys::W;
    arr[17] = Keys::T;
    arr[37] = Keys::L;
    arr[38] = Keys::J;
    arr[40] = Keys::K;
    arr[41] = Keys::SEMICOLON;

    arr[54] = Keys::RIGHT_CMD;
    arr[55] = Keys::LEFT_CMD;
    arr[59] = Keys::LEFT_CTRL;
    arr[60] = Keys::LEFT_SHIFT;
    arr[58] = Keys::RIGHT_ALT;

    return arr;
};

constexpr plat::types::NativeCodeToKeyArray nativeCodeToKeyArray{
    createNativeCodeToKeyArray()};
constexpr plat::types::NativeCodeToKey nativeCodeToKey =
    plat::types::NativeCodeToKey(nativeCodeToKeyArray);

constexpr auto createKeyToNativeCode() -> plat::types::KeyToNativeCode {
    plat::types::KeyToNativeCode keyToNativeCode{};

    using ::key::Keys;

    keyToNativeCode[Keys::A] = 0;
    keyToNativeCode[Keys::S] = 1;
    keyToNativeCode[Keys::T] = 17;
    keyToNativeCode[Keys::W] = 13;
    keyToNativeCode[Keys::J] = 38;

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
