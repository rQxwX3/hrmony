#ifndef APP_HPP
#define APP_HPP

#include <config.hpp>
#include <group.hpp>
#include <platform.hpp>

#include <memory>

namespace app {
class App {
  private:
    std::unique_ptr<grp::Group> m_globalGroup;
    std::unique_ptr<plt::Platform> m_platform;

    conf::Config m_config;

    bool m_running;

  public:
    App();

  public:
    auto run() -> void;

  public:
    [[nodiscard]] auto isRunning() const -> bool;

    [[nodiscard]] auto getConfig() const -> conf::Config;
    [[nodiscard]] auto getGlobalGroup() const -> const grp::Group *;

  public:
    static auto loadConfig() -> void;
};
} // namespace app

#endif // APP_HPP
