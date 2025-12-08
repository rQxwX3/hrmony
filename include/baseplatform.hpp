#include "app.hpp"
#include "iplatform.hpp"
#include "macosKeyCodes.hpp"
#include "types.hpp"

class BasePlatform : public IPlatform {
  protected:
    App *sApp{nullptr};

  private:
    Native2KeyMap sNative2KeyMap{MacOSKeyCodes::createNative2KeyMap()};
    Key2NativeMap sKey2NativeMap{MacOSKeyCodes::createKey2NativeMap()};

  public:
    [[nodiscard]] auto key2Native(Key key) -> NativeKeyCode;
    [[nodiscard]] auto native2Key(NativeKeyCode nativeKey) -> Key;
};
