#ifndef MACOS_HPP
#define MACOS_HPP

#include <app.hpp>
#include <platform.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace macOS {
class MacOS : public Platform {
  private:
    CFRunLoopRef m_runLoopRef;

    Combination m_currentBindedCombination;
    Event m_currentEvent;

    bool m_leaderUpProcessed;

  public:
    MacOS(App *appPtr);
    auto run() -> void override;
    ~MacOS() override;

  public:
    [[nodiscard]] auto modifierToCGEventFlags(key::Modifiers modifier) const
        -> CGEventFlags;

    [[nodiscard]] auto nativeCodeToModifier(NativeModifier nativeModifier) const
        -> key::Modifiers;

  public:
    auto setEventToCurrentCombination(Event &event) -> void override;

  public:
    auto setCurrentBindedCombination(const Combination &combination) -> void;
    auto setCurrentEvent(const Event &event) -> void;

  public:
    [[nodiscard]] auto getCurrentBindedCombination() const -> Combination;
    [[nodiscard]] auto getCurrentEvent() const -> Event;

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
