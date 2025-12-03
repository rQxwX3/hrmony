#include "app.hpp"
#include "iplatform.hpp"
#include "macosKeyCodes.hpp"
#include "types.hpp"

class BasePlatform : public IPlatform {
  protected:
    static inline eventCallback splatformToCore{nullptr};
    static inline const App *sApp{nullptr};

  private:
    static inline Native2KeyMap snative2KeyMap{
        MacOSKeyCodes::createNative2KeyMap()};
    static inline Key2NativeMap skey2NativeMap{
        MacOSKeyCodes::createKey2NativeMap()};

  public:
    [[nodiscard]] static auto key2Native(Key key) -> NativeKeyCode;
    [[nodiscard]] static auto native2Key(NativeKeyCode nativeKey) -> Key;

    static auto setEventCallback(eventCallback platformToCore) -> void;
};
