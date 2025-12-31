#include <app.hpp>
#include <config.hpp>
#include <platform.hpp>

plat::Platform::Platform(app::App *appPtr) : m_appPtr{appPtr} {};

[[nodiscard]] auto plat::Platform::getCurrentCombination() const
    -> const comb::Combination & {
    return m_currentCombination;
}

auto plat::Platform::resetCurrentCombination() -> void {
    m_currentCombination = comb::Combination();
}

auto plat::Platform::addToCurrentCombination(
    const comb::Combination &combination) -> void {
    const auto &modifiers{combination.getModifiers()};
    const auto modifiersCount{combination.getModifiersCount()};

    for (size_t i{0}; i != modifiersCount; ++i) {
        m_currentCombination.addModifier(modifiers.at(i));
    }

    const auto &regulars{combination.getRegulars()};
    const auto regularsCount{combination.getRegularsCount()};

    // TODO Supports only one key
    for (size_t i{0}; i != regularsCount; ++i) {
        m_currentCombination.addKey(regulars.at(i));
    }
}

[[nodiscard]] auto plat::Platform::getKeyBinding(const key::Keys key) const
    -> comb::Combination {
    const auto &config{getConfig()};

    const auto &bindedCombination{config.keyCombinationBinding.at(key)};

    return config.keyCombinationBinding.at(key);
}

[[nodiscard]] auto plat::Platform::getConfig() const -> conf::Config {
    return m_appPtr->getConfig();
}

[[nodiscard]] auto
plat::Platform::nativeCodeToKey(const NativeCode nativeCode) const
    -> key::Keys {
    const auto config{getConfig()};

    return config.nativeCodeToKey.at(nativeCode);
}

[[nodiscard]] auto plat::Platform::isHRMMode() const -> bool {
    return m_appPtr->isHRMMode();
}

auto plat::Platform::enterHRMMode() -> void { m_appPtr->toggleHRMMode(); }

auto plat::Platform::exitHRMMode() -> void {
    resetCurrentCombination();
    m_appPtr->toggleHRMMode();
}
