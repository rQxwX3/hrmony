#include <app.hpp>
#include <appDefaults.hpp>
#include <config.hpp>
#include <keys.hpp>
#include <macos.hpp>
#include <platform.hpp>

#include <memory>

#ifdef __APPLE__
App::App()
    : m_platform{std::make_unique<macOS::MacOS>(this)}, m_running{false},
      m_HRMMode{false}, m_config{conf::defaultConfig} {}
#endif

auto App::run() -> void {
    m_running = true;
    m_platform->run();
}

auto App::isRunning() const -> bool { return m_running; }

[[nodiscard]] auto App::getConfig() const -> conf::Config { return m_config; }

auto App::isHRMMode() const -> bool { return m_HRMMode; }

auto App::toggleHRMMode() -> void { m_HRMMode = !m_HRMMode; }
