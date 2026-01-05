#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <combination.hpp>
#include <config.hpp>
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

  public:
    Platform(app::App *appPtr = nullptr);

  public:
    auto enterHRMMode() -> void override;
    auto exitHRMMode() -> void override;

  public:
    auto addToCurrentCombination(const comb::Combination &combination)
        -> void override;

    auto resetCurrentCombination() -> void override;

  public:
    [[nodiscard]] auto nativeCodeToKey(NativeCode nativeCode) const
        -> key::Keys;

  public:
    [[nodiscard]] auto getCurrentCombination() const
        -> const comb::Combination &;

  public:
    [[nodiscard]] auto getBindedCombinations(key::Keys key) const
        -> grp::types::Combinations override;

    [[nodiscard]] auto getConfig() const -> conf::Config;

    [[nodiscard]] auto isHRMMode() const -> bool;
};
} // namespace plat

#endif // PLATFORM_HPP
