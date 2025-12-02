#ifndef MACOS_KEY_CODES
#define MACOS_KEY_CODES

#include "types.hpp"
#include <array>

static constexpr std::array<NativeKeyCode, static_cast<size_t>(Key::size)>
    skeyCodeMapData = {static_cast<CGKeyCode>(0), static_cast<CGKeyCode>(11),
                       static_cast<CGKeyCode>(8), static_cast<CGKeyCode>(2),
                       static_cast<CGKeyCode>(55)};

#endif // MACOS_KEY_CODES
