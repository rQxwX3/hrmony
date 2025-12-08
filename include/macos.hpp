#ifndef MACOS_HPP
#define MACOS_HPP

#include "app.hpp"
#include "baseplatform.hpp"

#include <ApplicationServices/ApplicationServices.h>

class MacOS : public BasePlatform {
  private:
    auto postEventToOS(const Event &event) -> void override;

    // MacOS requires a C-style function as callback, thus friend
    friend auto tapCallback(CGEventTapProxy proxy, CGEventType type,
                            CGEventRef event, void *refcon) -> CGEventRef;

    CFRunLoopRef m_runLoopRef;

  public:
    MacOS(App *appPtr);

    MacOS(MacOS &other) = delete;
    MacOS(MacOS &&other) = delete;

    auto operator=(MacOS &other) -> MacOS & = delete;
    auto operator=(MacOS &&other) -> MacOS & = delete;

    ~MacOS() override;
};

#endif // MACOS_HPP
