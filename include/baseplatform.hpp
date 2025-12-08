#include "app.hpp"
#include "iplatform.hpp"
#include "macosKeyCodes.hpp"
#include "types.hpp"

class BasePlatform : public IPlatform {
  protected:
    App *m_appPtr{nullptr};

  private:
    const inline static Native2KeyMap sNative2KeyMap{
        MacOSKeyCodes::createNative2KeyMap()};
    const inline static Key2NativeMap sKey2NativeMap{
        MacOSKeyCodes::createKey2NativeMap()};

  public:
    BasePlatform(App *appPtr);

    auto sendEventToCore(const Event &event) -> void override;
    auto onCoreEvent(const Event &event) -> void override;

    [[nodiscard]] auto static key2Native(Key key) -> NativeKeyCode;
    [[nodiscard]] auto static native2Key(NativeKeyCode nativeKey) -> Key;
};
