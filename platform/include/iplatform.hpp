#ifndef IPLATFORM_HPP
#define IPLATFORM_HPP

#include <combination.hpp>
#include <group.hpp>
#include <groupTypes.hpp>
#include <platformTypes.hpp>

class IPlatform {
  public:
    virtual auto run() -> void = 0;

  public:
    virtual auto addToCurrentCombination(const comb::Combination &combination)
        -> void = 0;

    virtual auto resetCurrentCombination() -> void = 0;

    virtual auto setEventToCombination(
        Event &event, const comb::Combination &combination) const -> void = 0;

    virtual auto enterGroup(const grp::Group *group) -> void = 0;
    virtual auto exitToGlobalGroup() -> void = 0;

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
