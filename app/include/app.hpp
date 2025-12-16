#ifndef APP_HPP
#define APP_HPP

#include <appDefaults.hpp>
#include <platform.hpp>

#include <memory>

class App {
  private:
    bool m_running{false};
    bool m_HRMMode{true};

    std::unique_ptr<Platform> m_platform{nullptr};

    KeyBindingArray m_keyBindingArray{AppDefaults::keyBindingArray};

  public:
    App();

    auto run() -> void;
    auto toggleHRMMode() -> void;

    [[nodiscard]] auto getKeyBinding(Keys::Printables key) const
        -> Keys::Modifiers;

    [[nodiscard]] auto isRunning() const -> bool;
    [[nodiscard]] auto isHRMMode() const -> bool;
};

#endif // APP_HPP
