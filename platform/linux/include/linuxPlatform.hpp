#ifndef LINUX_PLATFORM_HPP
#define LINUX_PLATFORM_HPP

#include "../../../core/include/event.hpp"
#include "../../../core/include/iplatform.hpp"

#include <ApplicationServices/ApplicationServices.h>

class LinuxPlatform : IPlatform {
    auto sendEvent(const Event &e) -> void;
};

#endif // LINUX_PLATFORM_HPP
