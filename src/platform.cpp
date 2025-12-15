#include "../include/platform.hpp"

Platform::Platform(const NativeKey2PrintableArr &nk2pa,
                   const Modifier2NativeModifierArr &m2nma, App *appPtr)
    : m_nativeKey2Printable{nk2pa}, m_modifier2NativeModifier{m2nma},
      m_appPtr{appPtr}, m_currentModifiers{Keys::Modifiers::NULLKEY},
      m_currentModifiersCnt{0} {};

auto Platform::setEventModifiersToCurrent(Event &event) -> void {
    for (const auto &modifier : m_currentModifiers) {
        if (modifier == Keys::Modifiers::NULLKEY) {
            continue;
        }

        CGEventSetFlags(event, modifier2NativeModifier(modifier));
    }
}

auto Platform::resetCurrentModifiers() -> void {
    m_currentModifiers = {Keys::Modifiers::NULLKEY};
    m_currentModifiersCnt = 0;
}

auto Platform::addCurrentModifier(const Keys::Modifiers modifier) -> void {
    m_currentModifiers.at(m_currentModifiersCnt) = modifier;
    m_currentModifiersCnt++;
}

[[nodiscard]] auto Platform::getAppPtr() const -> const App * {
    return m_appPtr;
}

[[nodiscard]] auto Platform::getKeyBinding(const Keys::Printables key) const
    -> Keys::Modifiers {
    return m_appPtr->getKeyBinding(key);
}

[[nodiscard]] auto
Platform::nativeKey2Printable(const NativeKeyCode nativeKey) const
    -> Keys::Printables {
    return m_nativeKey2Printable.at(static_cast<size_t>(nativeKey));
}

[[nodiscard]] auto
Platform::modifier2NativeModifier(const Keys::Modifiers modifier) const
    -> NativeModifier {
    return m_modifier2NativeModifier.at(static_cast<size_t>(modifier));
}

[[nodiscard]] auto Platform::isAppRunning() const -> bool {
    return m_appPtr->isRunning();
}

[[nodiscard]] auto Platform::isHRMMode() const -> bool {
    return m_appPtr->isHRMMode();
}
