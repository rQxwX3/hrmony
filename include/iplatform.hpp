#ifndef IPLATFORM_HPP
#define IPLATFORM_HPP

#include "event.hpp"

class IPlatform {
  public:
    virtual auto run() -> void = 0;
    virtual auto postEventToOS(const Event &event) -> void = 0;
    virtual auto sendEventToCore(const Event &event) -> void = 0;

    IPlatform() = default;

    IPlatform(const IPlatform &) = default;
    auto operator=(const IPlatform &) -> IPlatform & = default;
    IPlatform(IPlatform &&) = delete;
    auto operator=(IPlatform &&) -> IPlatform & = delete;
    virtual ~IPlatform() = default;
};

#endif // IPLATFORM_HPP
