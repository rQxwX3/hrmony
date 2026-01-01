#ifndef MACOS_HPP
#define MACOS_HPP

#include <app.hpp>
#include <combination.hpp>
#include <platform.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace mac {
class MacOS : public plat::Platform {
  private:
    CFRunLoopRef m_runLoopRef;

    NativeCode m_currentNativeCode;

    bool m_leaderUpProcessed;

  public:
    MacOS(app::App *appPtr);
    ~MacOS() override;

  public:
    auto run() -> void override;

  public:
    [[nodiscard]] auto modifierToCGEventFlags(key::Keys modifier) const
        -> CGEventFlags;

    [[nodiscard]] auto nativeCodeToKey(NativeCode nativeCode) const
        -> key::Keys;

    [[nodiscard]] auto keyToNativeCode(key::Keys key) const -> NativeCode;

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

    [[nodiscard]] auto getBindedCombination() const -> comb::Combination;

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
