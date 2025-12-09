#ifndef APP_HPP
#define APP_HPP

#include "core.hpp"
#include "iplatform.hpp"

#include <memory>

class App {
  private:
    bool m_running{false};
    bool m_HRMMode{true};

    std::unique_ptr<Core> m_core{nullptr};
    std::unique_ptr<IPlatform> m_platform{nullptr};

  public:
    App();

    auto run() -> void;

    [[nodiscard]] auto isRunning() const -> bool;
    [[nodiscard]] auto isHRMMode() const -> bool;

    auto sendEventToCore(const Event &event) -> void;
    auto sendEventToPlatform(const Event &event) -> void;

    auto toggleHRMMode() -> void;
};

#endif // APP_HPP
