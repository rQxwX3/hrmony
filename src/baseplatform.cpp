#include "../include/baseplatform.hpp"

auto BasePlatform::key2Native(Key key) -> NativeKeyCode {
    return skey2NativeMap.at(static_cast<size_t>(key));
}

auto BasePlatform::native2Key(NativeKeyCode nativeKey) -> Key {
    return snative2KeyMap.at(nativeKey);
}

auto BasePlatform::setEventCallback(eventCallback platformToCore) -> void {
    splatformToCore = std::move(platformToCore);
}

auto BasePlatform::setKey2NativeMap(const Key2NativeMap &key2NativeMap)
    -> void {
    skey2NativeMap = key2NativeMap;
}

auto BasePlatform::setNative2KeyMap(const Native2KeyMap &native2KeyMap)
    -> void {
    snative2KeyMap = native2KeyMap;
}
