#include <app.hpp>
#include <config.hpp>
#include <platform.hpp>

#include <optional>

namespace plt {
Platform::Platform(grp::Group *groupPtr, app::App *appPtr)
    : m_appPtr{appPtr}, m_currentNativeCode{0}, m_currentGroupPtr{groupPtr},
      m_leaderUpToBeProcessed{key::Keys::NULLKEY} {};

[[nodiscard]] auto
Platform::getCurrentCombination() const & -> const comb::Combination & {
    return m_currentCombination;
}

auto Platform::resetCurrentCombination() -> void {
    m_currentCombination = comb::Combination();
}

auto Platform::setCurrentGroup(const grp::Group *group) -> void {
    m_currentGroupPtr = const_cast<grp::Group *>(group);
    m_leaderUpToBeProcessed = key::Keys::NULLKEY;
}

auto Platform::resetCurrentGroup() -> void {
    setCurrentGroup(m_appPtr->getGlobalGroup());

    resetCurrentCombination();
}

auto Platform::addToCurrentCombination(const comb::Combination &combination)
    -> void {
    const auto [modifiersArray, modifiersCount]{combination.getModifiers()};

    for (size_t i{0}; i != modifiersCount; ++i) {
        m_currentCombination.addModifier(modifiersArray.at(i));
    }

    const auto [regularsArray, regularsCount]{combination.getRegulars()};

    for (size_t i{0}; i != regularsCount; ++i) {
        m_currentCombination.addKey(regularsArray.at(i));
    }
}

[[nodiscard]] auto Platform::getCurrentGroup() const -> const grp::Group * {
    return m_currentGroupPtr;
}

[[nodiscard]] auto Platform::getGroupAction() const
    -> const grp::types::Action & {
    const auto key{getCurrentKey()};

    const auto *currentGroup{getCurrentGroup()};
    return currentGroup->getAction(key);
}

[[nodiscard]] auto Platform::getConfig() const -> conf::Config {
    return m_appPtr->getConfig();
}

[[nodiscard]] auto Platform::nativeCodeToKey(const NativeCode nativeCode) const
    -> std::optional<key::Keys> {
    const auto config{getConfig()};

    return config.nativeCodeToKey.at(nativeCode);
}

[[nodiscard]] auto Platform::keyToNativeCode(key::Keys key) const
    -> std::optional<NativeCode> {
    const auto config{getConfig()};

    return config.keyToNativeCode.at(key);
}

[[nodiscard]] auto Platform::getCurrentKey() const -> key::Keys {
    const auto key{nativeCodeToKey(m_currentNativeCode)};

    if (!key.has_value()) {
        // TODO
    }

    return key.value();
}

auto Platform::setCurrentNativeCode(NativeCode nativeCode) -> void {
    m_currentNativeCode = nativeCode;
}

[[nodiscard]] auto Platform::getLeaderUpToBeProcessed() const -> key::Keys {
    return m_leaderUpToBeProcessed;
}

auto Platform::setLeaderUpToBeProcessed(const key::Keys leader) -> void {
    m_leaderUpToBeProcessed = leader;
}
} // namespace plt
