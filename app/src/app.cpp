#include <app.hpp>
#include <config.hpp>
#include <keys.hpp>
#include <macos.hpp>
#include <platform.hpp>

#include <memory>

#ifdef __APPLE__
app::App::App()
    : m_globalGroup{std::make_unique<grp::Group>(grp::createGlobalGroup())},
      m_platform{std::make_unique<mac::MacOS>(m_globalGroup.get(), this)},
      m_running{false}, m_config{conf::loadDefaultConfig()} {}
#endif

auto app::App::run() -> void {
    m_running = true;
    m_platform->run();
}

[[nodiscard]] auto app::App::isRunning() const -> bool { return m_running; }

[[nodiscard]] auto app::App::getConfig() const -> conf::Config {
    return m_config;
}

[[nodiscard]] auto app::App::getGlobalGroup() const -> const grp::Group * {
    return m_globalGroup.get();
}
