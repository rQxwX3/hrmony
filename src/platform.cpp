#include "../include/platform.hpp"

Platform::Platform(const NativeKey2PrintableArr &nk2pa,
                   const Modifier2NativeModifierArr &m2nma, App *appPtr)
    : m_nativeKey2Printable{nk2pa}, m_modifier2NativeModifier{m2nma},
      m_appPtr{appPtr} {};

[[nodiscard]] auto Platform::getAppPtr() const -> const App * {
    return m_appPtr;
}

[[nodiscard]] auto Platform::getKeyBinding(Keys::Printables key)
    -> Keys::Modifiers {
    return m_appPtr->getKeyBinding(key);
}

[[nodiscard]] auto Platform::nativeKey2Printable(NativeKeyCode nativeKey)
    -> Keys::Printables {
    return m_nativeKey2Printable.at(static_cast<size_t>(nativeKey));
}

[[nodiscard]] auto Platform::modifier2NativeModifier(Keys::Modifiers modifier)
    -> NativeModifier {
    return m_modifier2NativeModifier.at(static_cast<size_t>(modifier));
}
// auto Platform::sendKeyToApp(Keys::Printables key) -> void {
//     m_appPtr->onPlatformKey(event);
// }

// auto Platform::key2Native(Key key) -> NativeKeyCode {
//     return sKey2NativeMap.at(static_cast<size_t>(key));
// }
//
// auto Platform::native2Key(NativeKeyCode nativeKey) -> Key {
//     return sNative2KeyMap.at(nativeKey);
// }

// auto Platform::onAppEvent(const Event &event) -> void { postEventToOS(event);
// }

[[nodiscard]] auto Platform::isAppRunning() -> bool {
    return m_appPtr->isRunning();
}

[[nodiscard]] auto Platform::isHRMMode() -> bool {
    return m_appPtr->isHRMMode();
}
