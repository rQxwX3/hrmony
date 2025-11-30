#include "../include/app.hpp"
#include "../include/macos.hpp"
#include "../include/types.hpp"

#include <memory>

App::App(const sendEventCallback &coreToPlatform,
         const sendEventCallback &platformToCore)
    : m_running{true}, m_HRMMode{false},
      m_platform{std::make_unique<MacOS>(platformToCore)},
      m_core{std::make_unique<Core>(coreToPlatform)} {}

auto App::run() -> void { m_platform->startListening(); }

auto App::isRunning() const -> bool { return m_running; }

auto App::isHRMModeActive() const -> bool { return m_HRMMode; }
