#ifndef MACOS_CONSTANTS
#define MACOS_CONSTANTS

#include <keys.hpp>
#include <types.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace macOS::constants {
constexpr auto createNativeKey2Printable() -> NativeKey2PrintableArray {
    NativeKey2PrintableArray arr{};

    arr[0] = ::Keys::Printables::A;
    arr[1] = ::Keys::Printables::S;
    arr[2] = ::Keys::Printables::D;
    arr[3] = ::Keys::Printables::F;
    arr[4] = ::Keys::Printables::H;
    arr[12] = ::Keys::Printables::Q;
    arr[37] = ::Keys::Printables::L;
    arr[38] = ::Keys::Printables::J;
    arr[40] = ::Keys::Printables::K;
    arr[41] = ::Keys::Printables::SEMICOLON;

    return arr;
};

constexpr auto createModifier2NativeModifier() -> Modifier2NativeModifierArray {
    Modifier2NativeModifierArray arr{};

    arr[static_cast<size_t>(::Keys::Modifiers::CMD)] = kCGEventFlagMaskCommand;
    arr[static_cast<size_t>(::Keys::Modifiers::CTRL)] = kCGEventFlagMaskControl;
    arr[static_cast<size_t>(::Keys::Modifiers::SHIFT)] = kCGEventFlagMaskShift;
    arr[static_cast<size_t>(::Keys::Modifiers::ALT)] =
        kCGEventFlagMaskAlternate;

    return arr;
}

constexpr NativeKey2PrintableArray nativeKey2Printable{
    createNativeKey2Printable()};

constexpr Modifier2NativeModifierArray modifier2NativeModifier{
    createModifier2NativeModifier()};
} // namespace macOS::constants

#endif // MACOS_CONSTANTS
