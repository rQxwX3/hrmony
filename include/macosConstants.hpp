#ifndef MACOS_CONSTANTS
#define MACOS_CONSTANTS

#include "keys.hpp"
#include "types.hpp"

#include <ApplicationServices/ApplicationServices.h>

namespace MacOSConstants {
constexpr auto createNativeKey2Printable() -> NativeKey2PrintableArr {
    NativeKey2PrintableArr arr{};

    arr[0] = ::Keys::Printables::A;
    arr[1] = ::Keys::Printables::S;
    arr[2] = ::Keys::Printables::D;
    arr[3] = ::Keys::Printables::F;
    arr[4] = ::Keys::Printables::H;
    arr[12] = ::Keys::Printables::Q;
    arr[38] = ::Keys::Printables::J;

    return arr;
};

constexpr auto createModifier2NativeModifier() -> Modifier2NativeModifierArr {
    Modifier2NativeModifierArr arr{};

    arr[static_cast<size_t>(::Keys::Modifiers::CMD)] = kCGEventFlagMaskCommand;

    return arr;
}

constexpr NativeKey2PrintableArr nativeKey2Printable{
    createNativeKey2Printable()};

constexpr Modifier2NativeModifierArr modifier2NativeModifier{
    createModifier2NativeModifier()};
} // namespace MacOSConstants

#endif // MACOS_CONSTANTS
