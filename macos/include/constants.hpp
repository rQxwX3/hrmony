#ifndef MACOS_CONSTANTS
#define MACOS_CONSTANTS

#include <keys.hpp>
#include <types.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace macOS::constants {
constexpr auto createNativeKeyToPrintableArray() -> NativeKeyToPrintableArray {
    NativeKeyToPrintableArray arr{};

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

constexpr auto createModifier2NativeModifierArray()
    -> ModifierToNativeModifierArray {
    ModifierToNativeModifierArray arr{};

    using ::key::Modifiers;

    arr[static_cast<size_t>(Modifiers::CMD)] = kCGEventFlagMaskCommand;
    arr[static_cast<size_t>(Modifiers::CTRL)] = kCGEventFlagMaskControl;
    arr[static_cast<size_t>(Modifiers::SHIFT)] = kCGEventFlagMaskShift;
    arr[static_cast<size_t>(Modifiers::ALT)] = kCGEventFlagMaskAlternate;

    return arr;
}

constexpr auto createPrintable2NativeKey() -> PrintableToNativeKeyArray {
    PrintableToNativeKeyArray arr{};

    using ::key::Keys;

    arr[static_cast<size_t>(Keys::A)] = 0;
    arr[static_cast<size_t>(Keys::S)] = 1;
    arr[static_cast<size_t>(Keys::T)] = 17;
    arr[static_cast<size_t>(Keys::W)] = 13;

    return arr;
}

constexpr NativeKeyToPrintableArray nativeKey2PrintableArray{
    createNativeKeyToPrintableArray()};
constexpr NativeKeyToPrintable nativeKeyToPrintable =
    NativeKeyToPrintable(nativeKey2PrintableArray);

constexpr PrintableToNativeKeyArray printable2NativeKeyArray{
    createPrintable2NativeKey()};
constexpr PrintableToNativeKey printableToNativeKey{printable2NativeKeyArray};

constexpr ModifierToNativeModifierArray modifier2NativeModifierArray{
    createModifier2NativeModifierArray()};
constexpr ModifierToNativeModifier modifierToNativeModifier{
    modifier2NativeModifierArray};
} // namespace macOS::constants

#endif // MACOS_CONSTANTS
