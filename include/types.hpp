#ifndef TYPES_HPP
#define TYPES_HPP

#include <ApplicationServices/ApplicationServices.h>
#include <functional>

#include "keys.hpp"

#ifdef __APPLE__
using NativeKeyCode = CGKeyCode;
using NativeModifier = CGEventFlags;
using Event = CGEventRef;

static constexpr size_t maxKeyCode{127};
#endif

using eventCallback = std::function<void(const Event &event)>;

using NativeKey2PrintableArr = std::array<Keys::Printables, maxKeyCode>;
using Modifier2NativeModifierArr =
    std::array<CGEventFlags, static_cast<size_t>(Keys::Modifiers::m_size)>;

using KeyBindingArray =
    std::array<Keys::Modifiers, static_cast<size_t>(Keys::Printables::m_size)>;

#endif // TYPES_HPP
