#include "../include/app.hpp"
#include "../include/macos.hpp"

#include <memory>

App::App()
    : m_core{std::make_unique<Core>(this)},
      m_platform{std::make_unique<MacOS>(this)} {}

auto App::run() -> void {
    m_running = true;
    m_platform->run();
}

auto App::isRunning() const -> bool { return m_running; }

auto App::isHRMMode() const -> bool { return m_HRMMode; }

auto App::sendEventToCore(const Event &event) -> void {
    m_core->onPlatformEvent(event);
}

auto App::sendEventToPlatform(const Event &event) -> void {
    toggleHRMMode();
    m_platform->onCoreEvent(event);
}

auto App::toggleHRMMode() -> void { m_HRMMode = !m_HRMMode; }
