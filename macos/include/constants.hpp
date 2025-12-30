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

constexpr auto createKeyToNativeCodeArray()
    -> plat::types::KeyToNativeCodeArray {
    plat::types::KeyToNativeCodeArray arr{};

    using ::key::Keys;

    arr[static_cast<size_t>(Keys::A)] = 0;
    arr[static_cast<size_t>(Keys::S)] = 1;
    arr[static_cast<size_t>(Keys::T)] = 17;
    arr[static_cast<size_t>(Keys::W)] = 13;
    arr[static_cast<size_t>(Keys::J)] = 38;

    // Subtracting 1 is required because of Keys::m_regularsCount
    arr[static_cast<size_t>(Keys::RIGHT_CMD) - 1] = 55;
    arr[static_cast<size_t>(Keys::LEFT_CTRL) - 1] = 59;
    arr[static_cast<size_t>(Keys::LEFT_SHIFT) - 1] = 60;
    arr[static_cast<size_t>(Keys::RIGHT_ALT) - 1] = 58;

    return arr;
}

constexpr plat::types::KeyToNativeCodeArray keyToNativeCodeArray{
    createKeyToNativeCodeArray()};
constexpr plat::types::KeyToNativeCode keyToNativeCode{keyToNativeCodeArray};

using mac::types::ModifierToCGEventFlags,
    mac::types::ModifierToCGEventFlagsArray;

constexpr auto createModifierToCGEventFlagsArray()
    -> ModifierToCGEventFlagsArray {
    ModifierToCGEventFlagsArray arr{};

    using ::key::Keys;

    // Subracting key::regularsCount and 1 is required because regulars and
    // modifiers are in the same enum class
    arr[static_cast<size_t>(Keys::RIGHT_CMD) - key::regularsCount - 1] =
        kCGEventFlagMaskCommand;
    arr[static_cast<size_t>(Keys::LEFT_CTRL) - key::regularsCount - 1] =
        kCGEventFlagMaskControl;
    arr[static_cast<size_t>(Keys::LEFT_SHIFT) - key::regularsCount - 1] =
        kCGEventFlagMaskShift;
    arr[static_cast<size_t>(Keys::RIGHT_ALT) - key::regularsCount - 1] =
        kCGEventFlagMaskAlternate;

    return arr;
}

constexpr ModifierToCGEventFlagsArray modifierToCGEventFlagsArray{
    createModifierToCGEventFlagsArray()};
constexpr ModifierToCGEventFlags modifierToCGEventFlags{
    modifierToCGEventFlagsArray};
} // namespace mac::consts

#endif // MACOS_CONSTANTS_HPP
