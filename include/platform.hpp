#include "app.hpp"
#include "iplatform.hpp"
#include "types.hpp"

class Platform : public IPlatform {
  private:
    NativeKey2PrintableArray m_nativeKey2Printable;
    Modifier2NativeModifierArray m_modifier2NativeModifier;

    App *m_appPtr;

    std::array<Keys::Modifiers, maxModifierCnt> m_currentModifiers;
    size_t m_currentModifiersCnt;

  public:
    Platform(const NativeKey2PrintableArray &nk2pa,
             const Modifier2NativeModifierArray &m2nma, App *appPtr = nullptr);

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
