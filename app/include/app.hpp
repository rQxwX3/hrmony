#ifndef APP_HPP
#define APP_HPP

#include <config.hpp>
#include <group.hpp>
#include <platform.hpp>

#include <memory>

namespace app {
class App {
  private:
    std::unique_ptr<plat::Platform> m_platform;
    std::unique_ptr<grp::Group> m_globalGroup;

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
    [[nodiscard]] auto getGlobalGroup() const -> const grp::Group *;
};
} // namespace app

#endif // APP_HPP
