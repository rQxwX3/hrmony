#include "../include/app.hpp"
#include "../include/macos.hpp"
#include "../include/types.hpp"

#include <iostream>
#include <memory>

App::App()
    : m_running{true}, m_platform{std::make_unique<MacOS>()},
      m_core{std::make_unique<Core>()} {

    m_core->setEventCallback(
        [&](const Event &event) -> void { std::cout << "hello from core\n"; });
}

auto App::run() -> void { m_platform->run(); }

auto App::isRunning() const -> bool { return m_running; }

auto App::isHRMModeActive() const -> bool { return m_HRMMode; }
