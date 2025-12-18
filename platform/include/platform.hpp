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

    std::array<Keys::Modifiers, maxModifierCnt> m_currentModifiers;
    size_t m_currentModifiersCnt;

  public:
    Platform(App *appPtr = nullptr);

  public:
    auto enterHRMMode() -> void override;
    auto exitHRMMode() -> void override;

  public:
    auto addModifersArrayToCurrent(const ModifiersArray &modifiersArray)
        -> void override;

    auto resetCurrentModifiers() -> void override;

  public:
    [[nodiscard]] auto nativeKey2Printable(NativeKeyCode nativeKey) const
        -> Keys::Printables;

    [[nodiscard]] auto modifier2NativeModifier(Keys::Modifiers modifier) const
        -> NativeModifier;

  public:
    [[nodiscard]] auto getCurrentModifiers() const
        -> const CurrentModifiersArray &;

  public:
    [[nodiscard]] auto isAppRunning() const -> bool;

    [[nodiscard]] auto getKeyBinding(Keys::Printables key) const
        -> ModifiersArray override;

    [[nodiscard]] auto getConfig() const -> conf::Config;

    [[nodiscard]] auto isHRMMode() const -> bool;
};

#endif // PLATFORM_HPP
