#include <app.hpp>
#include <appDefaults.hpp>
#include <config.hpp>
#include <keys.hpp>
#include <macos.hpp>
#include <platform.hpp>

#include <memory>

#ifdef __APPLE__
App::App()
    : m_platform{std::make_unique<MacOS>(this)}, m_running{false},
      m_HRMMode{false}, m_keyBindingArray{AppDefaults::keyBindingArray},
      m_config{Config::defaultConfig} {}
#endif

auto App::run() -> void {
    m_running = true;
    m_platform->run();
}

auto App::isRunning() const -> bool { return m_running; }

auto App::isHRMMode() const -> bool { return m_HRMMode; }

// [[nodiscard]] auto App::getLeaderKey() const -> Keys::Modifiers {
//     return m_leaderKey;
// }
// [[nodiscard]] auto App::getExitKey() const -> Keys::Printables {
//     return m_exitKey;
// }

[[nodiscard]] auto App::getKeyBinding(const Keys::Printables key) const
    -> Keys::Modifiers {
    return m_keyBindingArray.at(static_cast<size_t>(key));
}

auto App::toggleHRMMode() -> void { m_HRMMode = !m_HRMMode; }
