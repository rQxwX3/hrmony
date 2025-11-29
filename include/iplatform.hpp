#ifndef IPLATFORM_HPP
#define IPLATFORM_HPP

#include "event.hpp"

struct IPlatform {
    virtual void sendEvent(const Event &e) = 0;
    virtual void startListening() = 0;

    IPlatform() = default;

    IPlatform(const IPlatform &) = default;
    auto operator=(const IPlatform &) -> IPlatform & = default;

    IPlatform(IPlatform &&) = delete;
    auto operator=(IPlatform &&) -> IPlatform & = delete;

    virtual ~IPlatform() = default;
};

#endif // IPLATFORM_HPP
