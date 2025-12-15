#ifndef TYPES_HPP
#define TYPES_HPP

#include <ApplicationServices/ApplicationServices.h>
#include <array>

#include "keys.hpp"

#ifdef __APPLE__
using NativeKeyCode = CGKeyCode;
using NativeModifier = CGEventFlags;
using Event = CGEventRef;
constexpr size_t maxKeyCode{128};
constexpr size_t maxModifierCnt{4};
#endif // __APPLE__

using NativeKey2PrintableArr = std::array<Keys::Printables, maxKeyCode>;

using Modifier2NativeModifierArr =
    std::array<NativeModifier, static_cast<size_t>(Keys::Modifiers::m_size)>;

using KeyBindingArray =
    std::array<Keys::Modifiers, static_cast<size_t>(Keys::Printables::m_size)>;

#endif // TYPES_HPP
