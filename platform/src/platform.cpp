#include <app.hpp>
#include <config.hpp>
#include <platform.hpp>

#include <iostream>

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

[[nodiscard]] auto Platform::getKeyBinding(const Keys::Printables key) const
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
Platform::nativeKey2Printable(const NativeKeyCode nativeKey) const
    -> Keys::Printables {
    return m_config.nativeKey2Printable.at(static_cast<size_t>(nativeKey));
}

[[nodiscard]] auto
Platform::modifier2NativeModifier(const Keys::Modifiers modifier) const
    -> NativeModifier {
    return m_config.modifier2NativeModifier.at(static_cast<size_t>(modifier));
}

[[nodiscard]] auto Platform::isHRMMode() const -> bool {
    return m_appPtr->isHRMMode();
}

auto Platform::enterHRMMode() -> void { m_appPtr->toggleHRMMode(); }

auto Platform::exitHRMMode() -> void {
    resetCurrentCombination();
    m_appPtr->toggleHRMMode();
}
