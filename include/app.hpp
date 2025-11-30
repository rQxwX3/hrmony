#ifndef APP_HPP
#define APP_HPP

#include "core.hpp"
#include "event.hpp"
#include "iplatform.hpp"
#include "types.hpp"

#include <memory>

class App {
  private:
    bool m_running;
    bool m_HRMMode;

    std::unique_ptr<IPlatform> m_platform;
    std::unique_ptr<Core> m_core;

  public:
    App(const sendEventCallback &coreToPlatform,
        const sendEventCallback &platformToCore);

    auto run() -> void;

    [[nodiscard]] auto isRunning() const -> bool;
    [[nodiscard]] auto isHRMModeActive() const -> bool;
};

#endif // APP_HPP
