#include "app.hpp"
#include "iplatform.hpp"
#include "macosKeyCodes.hpp"
#include "types.hpp"

class BasePlatform : public IPlatform {
  protected:
    static inline const App *sApp{nullptr};
    static inline const eventCallback sPlatformToCore{nullptr};

  private:
    static inline Native2KeyMap sNative2KeyMap{
        MacOSKeyCodes::createNative2KeyMap()};
    static inline Key2NativeMap sKey2NativeMap{
        MacOSKeyCodes::createKey2NativeMap()};

  public:
    [[nodiscard]] static auto key2Native(Key key) -> NativeKeyCode;
    [[nodiscard]] static auto native2Key(NativeKeyCode nativeKey) -> Key;
};
