#ifndef MACOS_HPP
#define MACOS_HPP

#include "app.hpp"
#include "baseplatform.hpp"

#include <CoreGraphics/CoreGraphics.h>

class MacOS : public BasePlatform {
  private:
    auto run() -> void override;
    auto postEventToOS(const Event &event) -> void override;
    auto sendEventToCore(const Event &event) -> void override;

    // MacOS requires a C-style function as callback, thus friend
    friend auto tapCallback(CGEventTapProxy proxy, CGEventType type,
                            CGEventRef event, void *refcon) -> CGEventRef;

  public:
    MacOS(App *appRef);
};

#endif // MACOS_HPP
