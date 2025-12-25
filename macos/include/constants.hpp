#ifndef MACOS_CONSTANTS
#define MACOS_CONSTANTS

#include <keys.hpp>
#include <types.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace macOS::constants {
constexpr auto createNativeKeyToPrintableArray() -> NativeKey2PrintableArray {
    NativeKey2PrintableArray arr{};

    using ::Keys::Printables;

    arr[0] = Printables::A;
    arr[1] = Printables::S;
    arr[2] = Printables::D;
    arr[3] = Printables::F;
    arr[4] = Printables::H;
    arr[12] = Printables::Q;
    arr[13] = Printables::W;
    arr[17] = Printables::T;
    arr[37] = Printables::L;
    arr[38] = Printables::J;
    arr[40] = Printables::K;
    arr[41] = Printables::SEMICOLON;

    return arr;
};

constexpr auto createModifier2NativeModifierArray()
    -> Modifier2NativeModifierArray {
    Modifier2NativeModifierArray arr{};

    using ::Keys::Modifiers;

    arr[static_cast<size_t>(Modifiers::CMD)] = kCGEventFlagMaskCommand;
    arr[static_cast<size_t>(Modifiers::CTRL)] = kCGEventFlagMaskControl;
    arr[static_cast<size_t>(Modifiers::SHIFT)] = kCGEventFlagMaskShift;
    arr[static_cast<size_t>(Modifiers::ALT)] = kCGEventFlagMaskAlternate;

    return arr;
}

constexpr auto createPrintable2NativeKey() -> Printable2NativeKeyArray {
    Printable2NativeKeyArray arr{};

    using ::Keys::Printables;

    arr[static_cast<size_t>(Printables::A)] = 0;
    arr[static_cast<size_t>(Printables::S)] = 1;
    arr[static_cast<size_t>(Printables::T)] = 17;
    arr[static_cast<size_t>(Printables::W)] = 13;

    return arr;
}

constexpr NativeKey2PrintableArray nativeKey2PrintableArray{
    createNativeKeyToPrintableArray()};
constexpr NativeKeyToPrintable nativeKeyToPrintable =
    NativeKeyToPrintable(nativeKey2PrintableArray);

constexpr Printable2NativeKeyArray printable2NativeKeyArray{
    createPrintable2NativeKey()};
constexpr PrintableToNativeKey printableToNativeKey{printable2NativeKeyArray};

constexpr Modifier2NativeModifierArray modifier2NativeModifierArray{
    createModifier2NativeModifierArray()};
constexpr ModifierToNativeModifier modifierToNativeModifier{
    modifier2NativeModifierArray};
} // namespace macOS::constants

#endif // MACOS_CONSTANTS
