#include "app.hpp"
#include "iplatform.hpp"
#include "types.hpp"

class Platform : public IPlatform {
  private:
    NativeKey2PrintableArr m_nativeKey2Printable;
    Modifier2NativeModifierArr m_modifier2NativeModifier;

    App *m_appPtr;

  protected:
    [[nodiscard]] auto getAppPtr() const -> const App *;

  public:
    Platform(const NativeKey2PrintableArr &nk2pa,
             const Modifier2NativeModifierArr &m2nma, App *appPtr = nullptr);

    [[nodiscard]] auto getKeyBinding(Keys::Printables key)
        -> Keys::Modifiers override;

    [[nodiscard]] auto nativeKey2Printable(NativeKeyCode nativeKey)
        -> Keys::Printables;

    [[nodiscard]] auto modifier2NativeModifier(Keys::Modifiers modifier)
        -> NativeModifier;

    [[nodiscard]] auto isAppRunning() -> bool;

    [[nodiscard]] auto isHRMMode() -> bool;

    // auto onAppEvent(const Event &event) -> void override;

    // [[nodiscard]] auto static key2Native(Key key) -> NativeKeyCode;
};
