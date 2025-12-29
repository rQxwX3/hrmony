#ifndef APP_HPP
#define APP_HPP

#include <config.hpp>
#include <platform.hpp>

#include <memory>

class App {
  private:
    std::unique_ptr<Platform> m_platform;

    conf::Config m_config;

    bool m_running;
    bool m_HRMMode;

  public:
    App();

    auto run() -> void;
    auto toggleHRMMode() -> void;

    [[nodiscard]] auto getConfig() const -> conf::Config;

  public:
    [[nodiscard]] auto isRunning() const -> bool;
    [[nodiscard]] auto isHRMMode() const -> bool;
};

#endif // APP_HPP
