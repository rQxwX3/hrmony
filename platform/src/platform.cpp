#include <app.hpp>
#include <config.hpp>
#include <platform.hpp>

Platform::Platform(App *appPtr)
    : m_appPtr{appPtr}, m_config{conf::defaultConfig} {};

[[nodiscard]] auto Platform::getCurrentCombination() const
    -> const Combination & {
    return m_currentCombination;
}

auto Platform::resetCurrentCombination() -> void {
    m_currentCombination = Combination();
}

auto Platform::addToCurrentCombination(const Combination &combination) -> void {
    const auto &modifiers{combination.getModifiers()};
    const auto modifiersCount{combination.getModifiersCount()};

    for (size_t i{0}; i != modifiersCount; ++i) {
        m_currentCombination.addModifier(modifiers.at(i));
    }

    const auto &keys{combination.getKeys()};
    const auto keysCount{combination.getKeysCount()};

    for (size_t i{0}; i != keysCount; ++i) {
        m_currentCombination.addKey(keys.at(i));
    }
}

[[nodiscard]] auto Platform::getKeyBinding(const key::Keys key) const
    -> Combination {
    const auto &config{getConfig()};

    const auto &bindedCombination{
        config.keyBindingArray.at(static_cast<size_t>(key))};

    return config.keyBindingArray.at(static_cast<size_t>(key));
}

[[nodiscard]] auto Platform::getConfig() const -> conf::Config {
    return m_config;
}

[[nodiscard]] auto
Platform::nativeKeyToPrintable(const NativeKeyCode nativeKey) const
    -> key::Keys {
    return m_config.nativeKeyToPrintable.at(nativeKey);
}

[[nodiscard]] auto
Platform::modifierToNativeModifier(const key::Modifiers modifier) const
    -> NativeModifier {
    return m_config.modifierToNativeModifier.at(modifier);
}

[[nodiscard]] auto Platform::isHRMMode() const -> bool {
    return m_appPtr->isHRMMode();
}

auto Platform::enterHRMMode() -> void { m_appPtr->toggleHRMMode(); }

auto Platform::exitHRMMode() -> void {
    resetCurrentCombination();
    m_appPtr->toggleHRMMode();
}
