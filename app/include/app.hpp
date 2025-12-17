#ifndef APP_HPP
#define APP_HPP

#include <config.hpp>
#include <platform.hpp>

#include <memory>

class App {
  private:
    std::unique_ptr<Platform> m_platform;

    bool m_running;
    bool m_HRMMode;

    KeyBindingArray m_keyBindingArray;

    Config::Config m_config;

  public:
    App();

    auto run() -> void;
    auto toggleHRMMode() -> void;

    [[nodiscard]] auto getKeyBinding(Keys::Printables key) const
        -> Keys::Modifiers;

    [[nodiscard]] auto isRunning() const -> bool;
    [[nodiscard]] auto isHRMMode() const -> bool;

    [[nodiscard]] auto getLeaderKey() const -> Keys::Modifiers;
    [[nodiscard]] auto getExitKey() const -> Keys::Printables;
};

#endif // APP_HPP
