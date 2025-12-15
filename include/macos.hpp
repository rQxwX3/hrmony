#ifndef MACOS_HPP
#define MACOS_HPP

#include "app.hpp"
#include "platform.hpp"

#include <ApplicationServices/ApplicationServices.h>

auto processKeyPress(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
                     void *refcon) -> CGEventRef;

class MacOS : public Platform {
  private:
    CFRunLoopRef m_runLoopRef;

  public:
    MacOS(App *appPtr);

    auto run() -> void override;

    ~MacOS() override;

  public:
    MacOS(const MacOS &other) = delete;
    MacOS(MacOS &&other) = delete;

    auto operator=(const MacOS &other) -> MacOS & = delete;
    auto operator=(MacOS &&other) -> MacOS & = delete;
};

#endif // MACOS_HPP
