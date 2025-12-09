#include "../include/platform.hpp"

Platform::Platform(App *appPtr) : m_appPtr{appPtr} {};

[[nodiscard]] auto Platform::getAppPtr() const -> const App * {
    return m_appPtr;
}

auto Platform::sendEventToCore(const Event &event) -> void {
    m_appPtr->sendEventToCore(event);
}

auto Platform::key2Native(Key key) -> NativeKeyCode {
    return sKey2NativeMap.at(static_cast<size_t>(key));
}

auto Platform::native2Key(NativeKeyCode nativeKey) -> Key {
    return sNative2KeyMap.at(nativeKey);
}

auto Platform::onCoreEvent(const Event &event) -> void { postEventToOS(event); }

[[nodiscard]] auto Platform::isAppRunning() -> bool {
    return m_appPtr->isRunning();
}

[[nodiscard]] auto Platform::isHRMMode() -> bool {
    return m_appPtr->isHRMMode();
}
