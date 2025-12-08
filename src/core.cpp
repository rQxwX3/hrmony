#include "../include/core.hpp"
#include "../include/app.hpp"

#include <iostream>

Core::Core(App *appPtr) : m_appPtr{appPtr} {}

auto Core::onPlatformEvent(const Event &event) -> void {
    std::cout << "received hello from platform\n";
    m_appPtr->sendEventToPlatform(event);
}
