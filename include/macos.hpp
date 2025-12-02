#ifndef MACOS_HPP
#define MACOS_HPP

#include "baseplatform.hpp"

#include <CoreGraphics/CoreGraphics.h>

class MacOS : public BasePlatform {
  private:
    auto startListening() -> void override;

    [[nodiscard]] static auto tapCallback(CGEventTapProxy proxy,
                                          CGEventType type, CGEventRef event,
                                          void *refcon) -> CGEventRef;

    auto postEvent(const Event &event) -> void override;

  public:
    MacOS() = default;
};

#endif // MACOS_HPP
