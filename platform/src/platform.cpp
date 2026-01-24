#include <app.hpp>
#include <appTypes.hpp>
#include <config.hpp>
#include <platform.hpp>

#include <optional>

plt::Platform::Platform(grp::Group *groupPtr, app::App *appPtr)
    : m_appPtr{appPtr}, m_currentNativeCode{0}, m_currentGroupPtr{groupPtr} {};

[[nodiscard]] auto
plt::Platform::getCurrentCombination() const & -> const comb::Combination & {
    return m_currentCombination;
}

auto plt::Platform::resetCurrentCombination() -> void {
    m_currentCombination = comb::Combination();
}

auto plt::Platform::setCurrentGroup(grp::Group *group) -> void {
    m_currentGroupPtr = group;
}

auto plt::Platform::addToCurrentCombination(
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

[[nodiscard]] auto plt::Platform::getCurrentGroup() const
    -> const grp::Group * {
    return m_currentGroupPtr;
}

[[nodiscard]] auto plt::Platform::getGroupAction() const
    -> const grp::types::Action & {
    const auto key{nativeCodeToKey(m_currentNativeCode)};

    if (!key.has_value()) {
        // TODO
    }

    const auto *currentGroup{getCurrentGroup()};
    return currentGroup->getAction(key.value());
}

[[nodiscard]] auto plt::Platform::getConfig() const -> conf::Config {
    return m_appPtr->getConfig();
}

[[nodiscard]] auto
plt::Platform::nativeCodeToKey(const NativeCode nativeCode) const
    -> std::optional<key::Keys> {
    const auto config{getConfig()};

    return config.nativeCodeToKey.at(nativeCode);
}

[[nodiscard]] auto plt::Platform::keyToNativeCode(key::Keys key) const
    -> std::optional<NativeCode> {
    const auto config{getConfig()};

    return config.keyToNativeCode.at(key);
}

[[nodiscard]] auto plt::Platform::getCurrentNativeCode() const -> NativeCode {
    return m_currentNativeCode;
}

auto plt::Platform::enterGroup(const grp::Group *group) -> void {
    setCurrentGroup(const_cast<grp::Group *>(group));
}

auto plt::Platform::exitToGlobalGroup() -> void {
    setCurrentGroup(const_cast<grp::Group *>(m_appPtr->getGlobalGroup()));
    resetCurrentCombination();
}

auto plt::Platform::setCurrentNativeCode(NativeCode nativeCode) -> void {
    m_currentNativeCode = nativeCode;
}
