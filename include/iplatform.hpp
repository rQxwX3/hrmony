#ifndef IPLATFORM_HPP
#define IPLATFORM_HPP

#include "event.hpp"

class IPlatform {
  public:
    virtual auto postEventToOS(const Event &event) -> void = 0;
    virtual auto sendEventToCore(const Event &event) -> void = 0;
    virtual auto onCoreEvent(const Event &event) -> void = 0;
    virtual auto run() -> void = 0;

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
