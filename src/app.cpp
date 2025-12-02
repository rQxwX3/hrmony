#include "../include/app.hpp"
#include "../include/macos.hpp"
#include "../include/types.hpp"

#include <iostream>
#include <memory>

App::App()
    : m_running{true}, m_HRMMode{false}, m_platform{std::make_unique<MacOS>()},
      m_core{std::make_unique<Core>()} {

    m_platform->setEventCallback([&](const Event &event) -> void {
        if (event.getKey() == Key::A) {
            std::cout << "A was hit\n";
        }
    });

    m_core->setEventCallback(
        [&](const Event &event) -> void { std::cout << "hello from core\n"; });
}

auto App::run() -> void { m_platform->startListening(); }

auto App::isRunning() const -> bool { return m_running; }

auto App::isHRMModeActive() const -> bool { return m_HRMMode; }
