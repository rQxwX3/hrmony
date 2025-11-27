#include "../include/event.hpp"
#include "../include/key.hpp"
#include "../include/macos.hpp"

#include <ApplicationServices/ApplicationServices.h>

MacOS::MacOS() {
    m_keyCodeMap[Key::A] = (CGKeyCode)0;
    m_keyCodeMap[Key::S] = (CGKeyCode)1;
}

auto MacOS::convertKey(const Key &k) const -> CGKeyCode {
    return m_keyCodeMap.at(k);
}

auto MacOS::sendEvent(const Event &e) -> void {
    CGEventRef eventRef{CGEventCreateKeyboardEvent(
        nullptr, convertKey(e.getKey()), e.isDown())};

    CGEventPost(kCGHIDEventTap, eventRef);

    CFRelease(eventRef);
}
