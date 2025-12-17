#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <config.hpp>
#include <iplatform.hpp>
#include <types.hpp>

class App;

class Platform : public IPlatform {
  private:
    App *m_appPtr;

    Config::Config m_config;

    std::array<Keys::Modifiers, maxModifierCnt> m_currentModifiers;
    size_t m_currentModifiersCnt;

  public:
    Platform(App *appPtr = nullptr);

  public:
    auto toggleHRMMode() -> void override;

  public:
    auto addCurrentModifier(Keys::Modifiers modifier) -> void override;

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
        -> Keys::Modifiers override;

    [[nodiscard]] auto isHRMMode() const -> bool;
};

#endif // PLATFORM_HPP
