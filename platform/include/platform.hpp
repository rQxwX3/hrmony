#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <config.hpp>
#include <iplatform.hpp>
#include <types.hpp>

class App;

class Platform : public IPlatform {
  private:
    App *m_appPtr;

    conf::Config m_config;

    Combination m_currentCombination;

  public:
    Platform(App *appPtr = nullptr);

  public:
    auto enterHRMMode() -> void override;
    auto exitHRMMode() -> void override;

  public:
    auto addToCurrentCombination(const Combination &combination)
        -> void override;

    auto resetCurrentCombination() -> void override;

  public:
    [[nodiscard]] auto nativeCodeToKey(NativeCode nativeCode) const
        -> key::Keys;

    [[nodiscard]] auto modifierToNativeModifier(key::Modifiers modifier) const
        -> NativeModifier;

  public:
    [[nodiscard]] auto getCurrentCombination() const -> const Combination &;

  public:
    [[nodiscard]] auto getKeyBinding(key::Keys key) const
        -> Combination override;

    [[nodiscard]] auto getConfig() const -> conf::Config;

    [[nodiscard]] auto isHRMMode() const -> bool;
};

#endif // PLATFORM_HPP
