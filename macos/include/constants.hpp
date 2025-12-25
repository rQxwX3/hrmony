#ifndef MACOS_CONSTANTS_HPP
#define MACOS_CONSTANTS_HPP

#include <keys.hpp>
#include <macosTypes.hpp>
#include <types.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace macOS::constants {
constexpr auto createNativeCodeToKeyArray() -> NativeCodeToKeyArray {
    NativeCodeToKeyArray arr{};

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

    return arr;
};

constexpr NativeCodeToKeyArray nativeCodeToKeyArray{
    createNativeCodeToKeyArray()};
constexpr NativeCodeToKey nativeCodeToKey =
    NativeCodeToKey(nativeCodeToKeyArray);

constexpr auto createKeyToNativeCodeArray() -> KeyToNativeCodeArray {
    KeyToNativeCodeArray arr{};

    using ::key::Keys;

    arr[static_cast<size_t>(Keys::A)] = 0;
    arr[static_cast<size_t>(Keys::S)] = 1;
    arr[static_cast<size_t>(Keys::T)] = 17;
    arr[static_cast<size_t>(Keys::W)] = 13;

    return arr;
}

constexpr KeyToNativeCodeArray keyToNativeCodeArray{
    createKeyToNativeCodeArray()};
constexpr KeyToNativeCode keyToNativeCode{keyToNativeCodeArray};

constexpr auto createModifierToNativeCodeArray() -> ModifierToNativeCodeArray {
    ModifierToNativeCodeArray arr{};

    using ::key::Modifiers;

    arr[static_cast<size_t>(Modifiers::CMD)] = 55;
    arr[static_cast<size_t>(Modifiers::CTRL)] = 59;
    arr[static_cast<size_t>(Modifiers::SHIFT)] = 60;
    arr[static_cast<size_t>(Modifiers::ALT)] = 58;

    return arr;
}

constexpr ModifierToNativeCodeArray modifierToNativeCodeArray{
    createModifierToNativeCodeArray()};
constexpr ModifierToNativeCode modifierToNativeCode{modifierToNativeCodeArray};

using macOS::types::ModifierToCGEventFlags,
    macOS::types::ModifierToCGEventFlagsArray;

constexpr auto createModifierToCGEventFlagsArray()
    -> ModifierToCGEventFlagsArray {
    ModifierToCGEventFlagsArray arr{};

    using ::key::Modifiers;

    arr[static_cast<size_t>(Modifiers::CMD)] = kCGEventFlagMaskCommand;
    arr[static_cast<size_t>(Modifiers::CTRL)] = kCGEventFlagMaskControl;
    arr[static_cast<size_t>(Modifiers::SHIFT)] = kCGEventFlagMaskShift;
    arr[static_cast<size_t>(Modifiers::ALT)] = kCGEventFlagMaskAlternate;

    return arr;
}

constexpr ModifierToCGEventFlagsArray modifierToCGEventFlagsArray{
    createModifierToCGEventFlagsArray()};
constexpr ModifierToCGEventFlags modifierToCGEventFlags{
    modifierToCGEventFlagsArray};
} // namespace macOS::constants

#endif // MACOS_CONSTANTS_HPP
