#include "../include/baseplatform.hpp"

auto BasePlatform::key2Native(Key key) -> NativeKeyCode {
    return skey2NativeMap[key];
}

auto BasePlatform::native2Key(NativeKeyCode nativeKey) -> Key {
    return snative2KeyMap[nativeKey];
}

auto BasePlatform::setEventCallback(eventCallback platformToCore) -> void {
    splatformToCore = std::move(platformToCore);
}

auto BasePlatform::setNative2KeyMap(
    const std::unordered_map<NativeKeyCode, Key> &native2KeyMap) -> void {
    snative2KeyMap = native2KeyMap;
}

auto BasePlatform::setKey2NativeMap(
    const std::unordered_map<Key, NativeKeyCode> &key2NativeMap) -> void {
    skey2NativeMap = key2NativeMap;
}
