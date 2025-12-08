#include "../include/baseplatform.hpp"
#include <iostream>

BasePlatform::BasePlatform(App *appPtr) : m_appPtr{appPtr} {};

auto BasePlatform::sendEventToCore(const Event &event) -> void {
    m_appPtr->sendEventToCore(event);
}

auto BasePlatform::key2Native(Key key) -> NativeKeyCode {
    return sKey2NativeMap.at(static_cast<size_t>(key));
}

auto BasePlatform::native2Key(NativeKeyCode nativeKey) -> Key {
    return sNative2KeyMap.at(nativeKey);
}

auto BasePlatform::onCoreEvent(const Event &event) -> void {
    std::cout << "received hello from core\n";
}
