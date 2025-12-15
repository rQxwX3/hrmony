#include "../include/app.hpp"
#include "../include/macos.hpp"

#include <memory>

App::App() : m_platform{std::make_unique<MacOS>(this)} {}

auto App::run() -> void {
    m_running = true;
    m_platform->run();
}

auto App::isRunning() const -> bool { return m_running; }

auto App::isHRMMode() const -> bool { return m_HRMMode; }

[[nodiscard]] auto App::getKeyBinding(const Keys::Printables key) const
    -> Keys::Modifiers {
    return m_keyBindingArray.at(static_cast<size_t>(key));
}

auto App::toggleHRMMode() -> void { m_HRMMode = !m_HRMMode; }
