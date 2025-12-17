#include <app.hpp>
#include <platform.hpp>

Platform::Platform(App *appPtr)
    : m_appPtr{appPtr}, m_config{appPtr->getConfig()},
      m_currentModifiers{Keys::Modifiers::NULLKEY}, m_currentModifiersCnt{0} {};

[[nodiscard]] auto Platform::getCurrentModifiers() const
    -> const CurrentModifiersArray & {
    return m_currentModifiers;
}

auto Platform::resetCurrentModifiers() -> void {
    m_currentModifiers = {Keys::Modifiers::NULLKEY};
    m_currentModifiersCnt = 0;
}

auto Platform::addCurrentModifier(const Keys::Modifiers modifier) -> void {
    m_currentModifiers.at(m_currentModifiersCnt) = modifier;
    m_currentModifiersCnt++;
}

[[nodiscard]] auto Platform::getKeyBinding(const Keys::Printables key) const
    -> Keys::Modifiers {
    return m_appPtr->getKeyBinding(key);
}

[[nodiscard]] auto
Platform::nativeKey2Printable(const NativeKeyCode nativeKey) const
    -> Keys::Printables {
    return m_config.m_nativeKey2Printable.at(static_cast<size_t>(nativeKey));
}

[[nodiscard]] auto
Platform::modifier2NativeModifier(const Keys::Modifiers modifier) const
    -> NativeModifier {
    return m_config.m_modifier2NativeModifier.at(static_cast<size_t>(modifier));
}

[[nodiscard]] auto Platform::isAppRunning() const -> bool {
    return m_appPtr->isRunning();
}

[[nodiscard]] auto Platform::isHRMMode() const -> bool {
    return m_appPtr->isHRMMode();
}

auto Platform::toggleHRMMode() -> void { m_appPtr->toggleHRMMode(); }
