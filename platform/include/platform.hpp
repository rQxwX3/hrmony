#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <combination.hpp>
#include <config.hpp>
#include <group.hpp>
#include <iplatform.hpp>
#include <platformTypes.hpp>

namespace app {
class App;
}

namespace plat {
class Platform : public IPlatform {
  private:
    app::App *m_appPtr;

    comb::Combination m_currentCombination;

    grp::Group *m_currentGroupPtr;

  public:
    Platform(grp::Group *groupPtr, app::App *appPtr = nullptr);

  public:
    auto enterGroup(const grp::Group *group) -> void override;
    auto exitToGlobalGroup() -> void override;

  public:
    auto setCurrentGroup(grp::Group *group) -> void;

    auto addToCurrentCombination(const comb::Combination &combination)
        -> void override;

    auto resetCurrentCombination() -> void override;

  public:
    [[nodiscard]] auto nativeCodeToKey(NativeCode nativeCode) const
        -> key::Keys;

  public:
    [[nodiscard]] auto getCurrentCombination() const
        -> const comb::Combination &;

    [[nodiscard]] auto getCurrentGroup() const -> const grp::Group *;

  public:
    [[nodiscard]] auto getConfig() const -> conf::Config;

    [[nodiscard]] auto isHRMMode() const -> bool;
};
} // namespace plat

#endif // PLATFORM_HPP
