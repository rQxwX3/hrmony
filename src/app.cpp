#include "../include/app.hpp"
#include "../include/macos.hpp"

#include <memory>

App::App() {
    m_platform = std::make_unique<MacOS>(this);
    m_core = std::make_unique<Core>(this);
}

auto App::run() -> void {
    m_platform->run();
    m_running = true;
}

auto App::isRunning() const -> bool { return m_running; }

auto App::isHRMModeActive() const -> bool { return m_HRMMode; }
