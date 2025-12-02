#ifndef TYPES_HPP
#define TYPES_HPP

#include "event.hpp"

#include <ApplicationServices/ApplicationServices.h>
#include <functional>

using eventCallback = std::function<void(const Event &event)>;

#ifdef __APPLE__
using NativeKeyCode = CGKeyCode;
#endif

#endif // TYPES_HPP
