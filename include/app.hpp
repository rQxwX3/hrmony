#ifndef APP_HPP
#define APP_HPP

#include "appDefaults.hpp"
#include "iplatform.hpp"

#include <memory>

class App {
  private:
    bool m_running{false};
    bool m_HRMMode{true};

    std::unique_ptr<IPlatform> m_platform{nullptr};

    KeyBindingArray m_keyBindingArray{AppDefaults::keyBindingArray};

  private:
    auto getKeyBinding(Keys::Printables key) -> Keys::Modifiers;

  public:
    App();

    auto run() -> void;

    auto onPlatformKey(Keys::Printables key) -> void;
    auto sendKeyToPlatform(Keys::Modifiers key) -> void;

    auto toggleHRMMode() -> void;

    [[nodiscard]] auto isRunning() const -> bool;
    [[nodiscard]] auto isHRMMode() const -> bool;
};

#endif // APP_HPP
