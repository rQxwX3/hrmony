#include "../include/app.hpp"
#include "../include/macos.hpp"

#include <iostream>
#include <memory>

App::App() {
    m_platform = std::make_unique<MacOS>(this);
    m_core = std::make_unique<Core>(this);
}

auto App::run() -> void { m_running = true; }

auto App::isRunning() const -> bool { return m_running; }

auto App::isHRMModeActive() const -> bool { return m_HRMMode; }

auto App::sendEventToCore(const Event &event) -> void {
    std::cout << "hello from platform\n";
    m_core->onPlatformEvent(event);
}

auto App::sendEventToPlatform(const Event &event) -> void {
    std::cout << "hello from core\n";
    m_platform->onCoreEvent(event);
}
