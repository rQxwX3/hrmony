#include "app.hpp"
#include "iplatform.hpp"
#include "macosKeyCodes.hpp"
#include "types.hpp"

class Platform : public IPlatform {
  private:
    App *m_appPtr;

  protected:
    [[nodiscard]] auto getAppPtr() const -> const App *;

  private:
    constexpr static Native2KeyMap sNative2KeyMap{
        MacOSKeyCodes::createNative2KeyMap()};
    constexpr static Key2NativeMap sKey2NativeMap{
        MacOSKeyCodes::createKey2NativeMap()};

  public:
    Platform(App *appPtr = nullptr);

    auto sendEventToCore(const Event &event) -> void override;
    auto onCoreEvent(const Event &event) -> void override;

    [[nodiscard]] auto static key2Native(Key key) -> NativeKeyCode;
    [[nodiscard]] auto static native2Key(NativeKeyCode nativeKey) -> Key;

    [[nodiscard]] auto isAppRunning() -> bool;
    [[nodiscard]] auto isHRMMode() -> bool;
};
