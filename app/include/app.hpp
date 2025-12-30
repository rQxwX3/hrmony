#ifndef APP_HPP
#define APP_HPP

#include <config.hpp>
#include <platform.hpp>

#include <memory>

namespace app {
class App {
  private:
    std::unique_ptr<plat::Platform> m_platform;

    conf::Config m_config;

    bool m_running;
    bool m_HRMMode;

  public:
    App();

  public:
    auto run() -> void;
    auto toggleHRMMode() -> void;

  public:
    [[nodiscard]] auto isRunning() const -> bool;
    [[nodiscard]] auto isHRMMode() const -> bool;

    [[nodiscard]] auto getConfig() const -> conf::Config;
};
} // namespace app

#endif // APP_HPP
