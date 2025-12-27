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

    arr[static_cast<size_t>(Modifiers::RIGHT_CMD)] = 55;
    arr[static_cast<size_t>(Modifiers::LEFT_CTRL)] = 59;
    arr[static_cast<size_t>(Modifiers::LEFT_SHIFT)] = 60;
    arr[static_cast<size_t>(Modifiers::RIGHT_ALT)] = 58;

    return arr;
}
constexpr ModifierToNativeCodeArray modifierToNativeCodeArray{
    createModifierToNativeCodeArray()};
constexpr ModifierToNativeCode modifierToNativeCode{modifierToNativeCodeArray};

constexpr size_t modifierNativeCodeOffsetFromZero = 54;

constexpr auto createNativeCodeToModifierArray()
    -> types::NativeCodeToModifierArray {
    types::NativeCodeToModifierArray arr{};

    using key::Modifiers;

    arr[0] = Modifiers::RIGHT_CMD;
    arr[1] = Modifiers::LEFT_CMD;
    arr[2] = Modifiers::LEFT_SHIFT;
    arr[4] = Modifiers::LEFT_ALT;
    arr[5] = Modifiers::LEFT_CTRL;
    arr[6] = Modifiers::RIGHT_SHIFT;
    arr[7] = Modifiers::RIGHT_ALT;

    return arr;
}

constexpr types::NativeCodeToModifierArray nativeCodeToModifierArray{
    createNativeCodeToModifierArray()};
constexpr types::NativeCodeToModifier nativeCodeToModifier{
    nativeCodeToModifierArray};

using macOS::types::ModifierToCGEventFlags,
    macOS::types::ModifierToCGEventFlagsArray;

constexpr auto createModifierToCGEventFlagsArray()
    -> ModifierToCGEventFlagsArray {
    ModifierToCGEventFlagsArray arr{};

    using ::key::Modifiers;

    arr[static_cast<size_t>(Modifiers::RIGHT_CMD)] = kCGEventFlagMaskCommand;
    arr[static_cast<size_t>(Modifiers::LEFT_CTRL)] = kCGEventFlagMaskControl;
    arr[static_cast<size_t>(Modifiers::LEFT_SHIFT)] = kCGEventFlagMaskShift;
    arr[static_cast<size_t>(Modifiers::RIGHT_ALT)] = kCGEventFlagMaskAlternate;

    return arr;
}

constexpr ModifierToCGEventFlagsArray modifierToCGEventFlagsArray{
    createModifierToCGEventFlagsArray()};
constexpr ModifierToCGEventFlags modifierToCGEventFlags{
    modifierToCGEventFlagsArray};
} // namespace macOS::constants

#endif // MACOS_CONSTANTS_HPP
