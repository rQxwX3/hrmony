#include "iplatform.hpp"

#include <unordered_map>

class BasePlatform : public IPlatform {
  protected:
    static inline eventCallback splatformToCore{nullptr};

  private:
    static inline std::unordered_map<NativeKeyCode, Key> snative2KeyMap{};
    static inline std::unordered_map<Key, NativeKeyCode> skey2NativeMap{};

  public:
    auto setEventCallback(eventCallback platformToCore) -> void override;

    [[nodiscard]] static auto key2Native(Key key) -> NativeKeyCode;
    [[nodiscard]] static auto native2Key(NativeKeyCode nativeKey) -> Key;

    static auto
    setNative2KeyMap(std::unordered_map<NativeKeyCode, Key> native2KeyMap)
        -> void;

    static auto
    setKey2NativeMap(std::unordered_map<Key, NativeKeyCode> key2NativeMap)
        -> void;
};
