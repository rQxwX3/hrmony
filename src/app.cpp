#include "../include/app.hpp"
#include "../include/macos.hpp"

#include <iostream>
#include <memory>

App::App()
    : m_running{true}, m_HRMMode{false},
      m_platform{std::make_unique<MacOS>([&]() -> void {
          m_HRMMode = !m_HRMMode;
          std::cout << "HRMMode is " << m_HRMMode << '\n';
      })} {

    m_platform->startListening();
}

auto App::isRunning() const -> bool { return m_running; }

auto App::isHRMModeActive() const -> bool { return m_HRMMode; }
