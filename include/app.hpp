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
    auto getRemappedKeys(Key key) -> Key;

  public:
    App();

    auto run() -> void;

    auto onPlatformEvent(const Event &event) -> void;
    auto sendEventToPlatform(const Event &event) -> void;

    auto toggleHRMMode() -> void;

    [[nodiscard]] auto isRunning() const -> bool;
    [[nodiscard]] auto isHRMMode() const -> bool;
};

#endif // APP_HPP
