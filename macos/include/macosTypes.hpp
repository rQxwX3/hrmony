#ifndef MACOS_TYPES
#define MACOS_TYPES

#include <ApplicationServices/ApplicationServices.h>

using NativeKeyCode = CGKeyCode;
using NativeModifier = CGEventFlags;
using Event = CGEventRef;
constexpr size_t maxKeyCode{128};

#endif
