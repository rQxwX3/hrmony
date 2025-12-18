#ifndef IPLATFORM_HPP
#define IPLATFORM_HPP

#include <types.hpp>

class IPlatform {
  public:
    virtual auto run() -> void = 0;

    [[nodiscard]] virtual auto getKeyBinding(Keys::Printables key) const
        -> ModifiersArray = 0;

  public:
    virtual auto addModifersArrayToCurrent(const ModifiersArray &modifiersArray)
        -> void = 0;

    virtual auto resetCurrentModifiers() -> void = 0;

    virtual auto setEventModifiersToCurrent(Event &event) -> void = 0;

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
