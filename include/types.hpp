#ifndef TYPES_HPP
#define TYPES_HPP

#include <ApplicationServices/ApplicationServices.h>
#include <functional>

#include "keys.hpp"

#ifdef __APPLE__
using NativeKeyCode = CGKeyCode;
using Event = CGEventRef;

static constexpr size_t maxKeyCode{127};
#endif

using eventCallback = std::function<void(const Event &event)>;

// using Native2KeyMap = std::array<Keys::Key, static_cast<size_t>(Key::size)>;
// using Key2NativeMap = std::array<NativeKeyCode, maxKeyCode>;

using KeyBindingArray =
    std::array<Keys::Modifiers, static_cast<size_t>(Keys::Printables::m_size)>;

#endif // TYPES_HPP
