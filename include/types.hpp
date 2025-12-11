#ifndef TYPES_HPP
#define TYPES_HPP

#include "event.hpp"

#include <ApplicationServices/ApplicationServices.h>
#include <functional>

using eventCallback = std::function<void(const Event &event)>;

#ifdef __APPLE__
using NativeKeyCode = CGKeyCode;

static constexpr size_t maxKeyCode{127};
#endif

using Native2KeyMap = std::array<Key, static_cast<size_t>(Key::size)>;
using Key2NativeMap = std::array<NativeKeyCode, maxKeyCode>;

using KeyBindingArray = std::array<Key, static_cast<size_t>(Key::size)>;

#endif // TYPES_HPP
