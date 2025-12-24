#ifndef MACOS_CONSTANTS
#define MACOS_CONSTANTS

#include <keys.hpp>
#include <types.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace macOS::constants {
constexpr auto createNativeKey2Printable() -> NativeKey2PrintableArray {
    NativeKey2PrintableArray arr{};

    using ::Keys::Printables;

    arr[0] = Printables::A;
    arr[1] = Printables::S;
    arr[2] = Printables::D;
    arr[3] = Printables::F;
    arr[4] = Printables::H;
    arr[12] = Printables::Q;
    arr[37] = Printables::L;
    arr[38] = Printables::J;
    arr[40] = Printables::K;
    arr[41] = Printables::SEMICOLON;

    return arr;
};

constexpr auto createModifier2NativeModifier() -> Modifier2NativeModifierArray {
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

    return arr;
}

constexpr NativeKey2PrintableArray nativeKey2Printable{
    createNativeKey2Printable()};

constexpr Modifier2NativeModifierArray modifier2NativeModifier{
    createModifier2NativeModifier()};

constexpr Printable2NativeKeyArray printable2NativeKey{
    createPrintable2NativeKey()};
} // namespace macOS::constants

#endif // MACOS_CONSTANTS
