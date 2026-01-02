#ifndef IPLATFORM_HPP
#define IPLATFORM_HPP

#include <appTypes.hpp>
#include <platformTypes.hpp>

class IPlatform {
  public:
    virtual auto run() -> void = 0;

    [[nodiscard]] virtual auto getBindedCombinations(key::Keys key) const
        -> app::types::Combinations = 0;

  public:
    virtual auto addToCurrentCombination(const comb::Combination &combination)
        -> void = 0;

    virtual auto resetCurrentCombination() -> void = 0;

    virtual auto setEventToCombination(
        Event &event, const comb::Combination &combination) const -> void = 0;

    virtual auto enterHRMMode() -> void = 0;
    virtual auto exitHRMMode() -> void = 0;

  public:
    IPlatform() = default;

  public:
    auto operator=(const IPlatform &) -> IPlatform & = default;
    virtual ~IPlatform() = default;

    IPlatform(IPlatform &&) = delete;
    IPlatform(const IPlatform &) = delete;
    auto operator=(IPlatform &&) -> IPlatform & = delete;
};

#endif // IPLATFORM_HPP
