#include "../include/core.hpp"

#include <iostream>

Core::Core(App *appPtr) { Core::sApp = appPtr; }

auto Core::onPlatformEvent(const Event &event) -> void {
    std::cout << "hello from core\n";
}
