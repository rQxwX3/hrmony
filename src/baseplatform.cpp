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
