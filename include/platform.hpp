#include "app.hpp"
#include "iplatform.hpp"
#include "types.hpp"

class Platform : public IPlatform {
  private:
    NativeKey2PrintableArr m_nativeKey2Printable;
    Modifier2NativeModifierArr m_modifier2NativeModifier;

    App *m_appPtr;

    std::array<Keys::Modifiers, maxModifierCnt> m_currentModifiers;
    size_t m_currentModifiersCnt;

  protected:
    [[nodiscard]] auto getAppPtr() const -> const App *;

  public:
    Platform(const NativeKey2PrintableArr &nk2pa,
             const Modifier2NativeModifierArr &m2nma, App *appPtr = nullptr);

    [[nodiscard]] auto nativeKey2Printable(NativeKeyCode nativeKey) const
        -> Keys::Printables;

    [[nodiscard]] auto modifier2NativeModifier(Keys::Modifiers modifier) const
        -> NativeModifier;

  public:
    auto addCurrentModifier(Keys::Modifiers modifier) -> void;

    auto resetCurrentModifiers() -> void;

    auto setEventModifiersToCurrent(Event &event) -> void;

  public:
    [[nodiscard]] auto isAppRunning() const -> bool;

    [[nodiscard]] auto getKeyBinding(Keys::Printables key) const
        -> Keys::Modifiers override;

    [[nodiscard]] auto isHRMMode() const -> bool;
};
