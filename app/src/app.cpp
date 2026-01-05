#include <app.hpp>
#include <config.hpp>
#include <keys.hpp>
#include <macos.hpp>
#include <platform.hpp>

#include <memory>

#ifdef __APPLE__
app::App::App()
    : m_platform{std::make_unique<mac::MacOS>(this)}, m_running{false},
      m_HRMMode{false}, m_config{conf::defaultConfig} {}
#endif

auto app::App::run() -> void {
    m_running = true;
    m_platform->run();
}

[[nodiscard]] auto app::App::isRunning() const -> bool { return m_running; }

[[nodiscard]] auto app::App::getConfig() const -> conf::Config {
    return m_config;
}

[[nodiscard]] auto app::App::isHRMMode() const -> bool { return m_HRMMode; }

auto app::App::toggleHRMMode() -> void { m_HRMMode = !m_HRMMode; }
