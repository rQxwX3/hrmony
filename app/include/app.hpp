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

  public:
    App();

    auto run() -> void;
    auto toggleHRMMode() -> void;

  public:
    [[nodiscard]] auto getKeyBinding(Keys::Printables key) const
        -> ModifiersArray;

    [[nodiscard]] auto isRunning() const -> bool;
    [[nodiscard]] auto isHRMMode() const -> bool;
};

#endif // APP_HPP
