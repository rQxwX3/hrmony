#ifndef MACOS_HPP
#define MACOS_HPP

#include "app.hpp"
#include "baseplatform.hpp"

#include <CoreGraphics/CoreGraphics.h>

class MacOS : public BasePlatform {
  private:
    auto run() -> void override;

    auto postEventToOS(const Event &event) -> void override;

    [[nodiscard]] static auto tapCallback(CGEventTapProxy proxy,
                                          CGEventType type, CGEventRef event,
                                          void *refcon) -> CGEventRef;

  public:
    MacOS(const App *appRef);
};

#endif // MACOS_HPP
