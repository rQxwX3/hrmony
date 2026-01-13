#ifndef MACOS_HPP
#define MACOS_HPP

#include <app.hpp>
#include <combination.hpp>
#include <platform.hpp>

#include <ApplicationServices/ApplicationServices.h>
#include <optional>

namespace mac {
class MacOS : public plat::Platform {
  private:
    CFRunLoopRef m_runLoopRef;

    NativeCode m_currentNativeCode;

    bool m_leaderUpProcessed;

  public:
    MacOS(grp::Group *groupPtr, app::App *appPtr);
    ~MacOS() override;

  public:
    auto run() -> void override;

  public:
    [[nodiscard]] auto modifierToCGEventFlags(key::Keys modifier) const
        -> std::optional<CGEventFlags>;

  public:
    auto setEventFlagsToModifiers(Event &event,
                                  comb::types::Modifiers modifiers) const
        -> void;

    auto setEventToCombination(Event &event,
                               const comb::Combination &combination) const
        -> void override;

  public:
    auto setCurrentNativeCode(NativeCode nativeCode) -> void;

  public:
    [[nodiscard]] auto getCurrentNativeCode() const -> NativeCode;

  public:
    [[nodiscard]] auto isLeaderUpProcessed() const -> bool;

    auto toggleLeaderUpProcessed() -> void;

  public:
    MacOS(const MacOS &other) = delete;
    MacOS(MacOS &&other) = delete;

    auto operator=(const MacOS &other) -> MacOS & = delete;
    auto operator=(MacOS &&other) -> MacOS & = delete;
};
} // namespace mac

#endif // MACOS_HPP
