#ifndef MACOS_HPP
#define MACOS_HPP

#include "app.hpp"
#include "platform.hpp"
#include "types.hpp"

#include <ApplicationServices/ApplicationServices.h>
#include <array>

auto processKeyPress(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
                     void *refcon) -> CGEventRef;

class MacOS : public Platform {
  private:
    CFRunLoopRef m_runLoopRef;

    std::array<Keys::Modifiers, maxModifierCnt> m_currentModifiers{
        Keys::Modifiers::NULLKEY};

    size_t m_currentModifiersCnt{0};

  public:
    MacOS(App *appPtr);

    auto run() -> void override;

    auto addCurrentModifier(Keys::Modifiers modifier) -> void;

    auto resetCurrentModifiers() -> void;

    auto setEventModifiersToCurrent(Event &event) -> void;

    ~MacOS() override;

  public:
    MacOS(const MacOS &other) = delete;
    MacOS(MacOS &&other) = delete;

    auto operator=(const MacOS &other) -> MacOS & = delete;
    auto operator=(MacOS &&other) -> MacOS & = delete;
};

#endif // MACOS_HPP
