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
