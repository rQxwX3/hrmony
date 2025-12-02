#ifndef APP_HPP
#define APP_HPP

#include "core.hpp"
#include "iplatform.hpp"

#include <memory>

class App {
  private:
    bool m_running{false};
    bool m_HRMMode{false};

    std::unique_ptr<IPlatform> m_platform{nullptr};
    std::unique_ptr<Core> m_core{nullptr};

  public:
    App();

    auto run() -> void;

    [[nodiscard]] auto isRunning() const -> bool;
    [[nodiscard]] auto isHRMModeActive() const -> bool;
};

#endif // APP_HPP
