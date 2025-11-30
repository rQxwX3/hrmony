#ifndef IPLATFORM_HPP
#define IPLATFORM_HPP

#include "event.hpp"
#include "types.hpp"

class IPlatform {
  protected:
    static inline sendEventCallback splatformToCore{nullptr};

  public:
    virtual auto postEvent(const Event &e) -> void = 0;
    virtual auto startListening() -> void = 0;
    virtual auto setEventCallback(sendEventCallback callback) -> void = 0;

    IPlatform() = default;

    IPlatform(const IPlatform &) = default;
    auto operator=(const IPlatform &) -> IPlatform & = default;

    IPlatform(IPlatform &&) = delete;
    auto operator=(IPlatform &&) -> IPlatform & = delete;

    virtual ~IPlatform() = default;
};

#endif // IPLATFORM_HPP
