#include "iplatform.hpp"
#include "types.hpp"

class BasePlatform : public IPlatform {
  protected:
    static inline eventCallback splatformToCore{nullptr};

  private:
    static inline Native2KeyMap snative2KeyMap{};
    static inline Key2NativeMap skey2NativeMap{};

  public:
    auto setEventCallback(eventCallback platformToCore) -> void override;

    [[nodiscard]] static auto key2Native(Key key) -> NativeKeyCode;
    [[nodiscard]] static auto native2Key(NativeKeyCode nativeKey) -> Key;

    static auto setNative2KeyMap(const Native2KeyMap &native2KeyMap) -> void;
    static auto setKey2NativeMap(const Key2NativeMap &key2NativeMap) -> void;
};
