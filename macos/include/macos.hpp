#ifndef MACOS_HPP
#define MACOS_HPP

#include <app.hpp>
#include <platform.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace macOS {
class MacOS : public Platform {
  private:
    CFRunLoopRef m_runLoopRef;

    bool m_leaderUpProcessed;

  public:
    MacOS(App *appPtr);
    auto run() -> void override;
    ~MacOS() override;

  public:
    auto setEventToCurrentCombination(Event &event) -> void override;

  public:
    [[nodiscard]] auto isLeaderUpProcessed() const -> bool;

    auto toggleLeaderUpProcessed() -> void;

  public:
    MacOS(const MacOS &other) = delete;
    MacOS(MacOS &&other) = delete;

    auto operator=(const MacOS &other) -> MacOS & = delete;
    auto operator=(MacOS &&other) -> MacOS & = delete;
};
} // namespace macOS

#endif // MACOS_HPP
