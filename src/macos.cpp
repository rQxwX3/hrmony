#include "../include/macos.hpp"
#include "../include/event.hpp"
#include "../include/key.hpp"

#include <ApplicationServices/ApplicationServices.h>

auto MacOS::tapCallback(CGEventTapProxy proxy, CGEventType type,
                        CGEventRef event, void *refcon) -> CGEventRef {
    return event;
}

auto MacOS::startListening() -> void {
    CGEventMask eventMask{CGEventMaskBit(kCGEventKeyDown) |
                          CGEventMaskBit(kCGEventKeyUp) |
                          CGEventMaskBit(kCGEventFlagsChanged)};

    CFMachPortRef machPortRef{CGEventTapCreate(
        kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
        eventMask, tapCallback, nullptr)};

    if (nullptr == machPortRef) {
        exit(1);
    }

    CFRunLoopSourceRef runLoopSourceRef{
        CFMachPortCreateRunLoopSource(kCFAllocatorDefault, machPortRef, 0)};

    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSourceRef,
                       kCFRunLoopCommonModes);
    CGEventTapEnable(machPortRef, true);
    CFRunLoopRun();
}

MacOS::MacOS() = default;

auto MacOS::convertKey(const Key &k) const -> CGKeyCode {
    return m_keyCodeMap.at(k);
}

auto MacOS::sendEvent(const Event &e) -> void {
    CGEventRef eventRef{CGEventCreateKeyboardEvent(
        nullptr, convertKey(e.getKey()), e.isDown())};

    CGEventPost(kCGHIDEventTap, eventRef);

    CFRelease(eventRef);
}
