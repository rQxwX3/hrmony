#ifndef MAC_PLATFORM_HPP
#define MAC_PLATFORM_HPP

#include "../../../core/include/event.hpp"
#include "../../../core/include/iplatform.hpp"

#include <ApplicationServices/ApplicationServices.h>

class MacPlatform : public IPlatform {
    auto sendEvent(const Event &e) -> void;
};

#endif // MAC_PLATFORM_HPP
