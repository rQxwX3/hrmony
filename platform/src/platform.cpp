#include <app.hpp>
#include <appTypes.hpp>
#include <config.hpp>
#include <platform.hpp>

plat::Platform::Platform(grp::Group *groupPtr, app::App *appPtr)
    : m_appPtr{appPtr}, m_currentGroupPtr{groupPtr} {};

[[nodiscard]] auto plat::Platform::getCurrentCombination() const
    -> const comb::Combination & {
    return m_currentCombination;
}

auto plat::Platform::resetCurrentCombination() -> void {
    m_currentCombination = comb::Combination();
}

auto plat::Platform::setCurrentGroup(grp::Group *group) -> void {
    m_currentGroupPtr = group;
}

auto plat::Platform::addToCurrentCombination(
    const comb::Combination &combination) -> void {
    const auto [modifiersArray, modifiersCount]{combination.getModifiers()};

    for (size_t i{0}; i != modifiersCount; ++i) {
        m_currentCombination.addModifier(modifiersArray.at(i));
    }

    const auto [regularsArray, regularsCount]{combination.getRegulars()};

    for (size_t i{0}; i != regularsCount; ++i) {
        m_currentCombination.addKey(regularsArray.at(i));
    }
}

[[nodiscard]] auto
plat::Platform::getBindedCombinations(const key::Keys key) const
    -> grp::types::Combinations {
    const auto &config{getConfig()};

    // const auto &bindedCombination{config.keyCombinationBinding.at(key)};

    // TODO fix
    return {};
    // return config.keyCombinationBinding.at(key);
}

[[nodiscard]] auto plat::Platform::getCurrentGroup() const
    -> const grp::Group * {
    return m_currentGroupPtr;
}

[[nodiscard]] auto plat::Platform::getConfig() const -> conf::Config {
    return m_appPtr->getConfig();
}

[[nodiscard]] auto plat::Platform::getGlobalGroup() const
    -> const grp::Group * {
    return m_appPtr->getGlobalGroup();
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

auto plat::Platform::enterGroup(const grp::Group *group) -> void {
    setCurrentGroup(const_cast<grp::Group *>(group));
    m_appPtr->toggleHRMMode();
}

auto plat::Platform::exitAllGroups() -> void {
    setCurrentGroup(nullptr);
    resetCurrentCombination();
    m_appPtr->toggleHRMMode();
}
