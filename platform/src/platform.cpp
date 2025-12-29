#include <app.hpp>
#include <config.hpp>
#include <platform.hpp>

Platform::Platform(App *appPtr) : m_appPtr{appPtr} {};

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
    return m_appPtr->getConfig();
}

[[nodiscard]] auto Platform::nativeCodeToKey(const NativeCode nativeCode) const
    -> key::Keys {
    const auto config{getConfig()};

    return config.nativeCodeToKey.at(nativeCode);
}

[[nodiscard]] auto
Platform::modifierToNativeModifier(const key::Modifiers modifier) const
    -> NativeModifier {
    const auto config{getConfig()};

    return config.modifierToCGEventFlags.at(modifier);
}

[[nodiscard]] auto Platform::isHRMMode() const -> bool {
    return m_appPtr->isHRMMode();
}

auto Platform::enterHRMMode() -> void { m_appPtr->toggleHRMMode(); }

auto Platform::exitHRMMode() -> void {
    resetCurrentCombination();
    m_appPtr->toggleHRMMode();
}
