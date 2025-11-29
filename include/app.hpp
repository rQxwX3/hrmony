#ifndef APP_HPP
#define APP_HPP

#include "../include/baseplatform.hpp"
#include <memory>

class App {
  private:
    bool m_running;
    bool m_HRMMode;
    std::unique_ptr<BasePlatform> m_platform;

  public:
    App();

    [[nodiscard]] auto isRunning() const -> bool;
    [[nodiscard]] auto isHRMModeActive() const -> bool;
};

#endif // APP_HPP
