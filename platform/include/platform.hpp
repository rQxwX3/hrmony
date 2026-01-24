#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <combination.hpp>
#include <config.hpp>
#include <group.hpp>
#include <platformTypes.hpp>

namespace app {
class App;
}

namespace plt {
class Platform {
  private:
    app::App *m_appPtr;
    NativeCode m_currentNativeCode;
    comb::Combination m_currentCombination;
    grp::Group *m_currentGroupPtr;

  public:
    Platform(grp::Group *groupPtr, app::App *appPtr = nullptr);
    virtual auto run() -> void = 0;
    virtual ~Platform() = default;

  public:
    auto enterGroup(const grp::Group *group) -> void;
    auto exitToGlobalGroup() -> void;

  public:
    auto setCurrentNativeCode(NativeCode nativeCode) -> void;
    auto setCurrentGroup(grp::Group *group) -> void;
    auto addToCurrentCombination(const comb::Combination &combination) -> void;
    auto resetCurrentCombination() -> void;

  public:
    [[nodiscard]] auto nativeCodeToKey(NativeCode nativeCode) const
        -> std::optional<key::Keys>;
    [[nodiscard]] auto keyToNativeCode(key::Keys key) const
        -> std::optional<NativeCode>;

  public:
    [[nodiscard]] auto getCurrentNativeCode() const -> NativeCode;
    [[nodiscard]] auto
    getCurrentCombination() const & -> const comb::Combination &;
    [[nodiscard]] auto getCurrentGroup() const -> const grp::Group *;
    [[nodiscard]] auto getGroupAction() const -> const grp::types::Action &;

  public:
    [[nodiscard]] auto getConfig() const -> conf::Config;
};
} // namespace plt

#endif // PLATFORM_HPP
