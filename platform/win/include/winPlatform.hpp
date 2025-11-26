#ifndef WIN_PLATFORM_HPP
#define WIN_PLATFORM_HPP

#include "../../../core/include/event.hpp"
#include "../../../core/include/iplatform.hpp"

#include <ApplicationServices/ApplicationServices.h>

class WinPlatform : IPlatform {
    auto sendEvent(const Event &e) -> void;
};

#endif // WIN_PLATFORM_HPP
