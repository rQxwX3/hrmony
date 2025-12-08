#include "../include/macos.hpp"

#include <ApplicationServices/ApplicationServices.h>
#include <iostream>

MacOS::MacOS(App *app) { MacOS::sApp = app; }

auto MacOS::sendEventToCore(const Event &event) -> void {
    std::cout << "hello from macos\n";
}

auto MacOS::postEventToOS(const Event &event) -> void {
    CGEventRef eventRef{CGEventCreateKeyboardEvent(
        nullptr, key2Native(event.getKey()), event.isDown())};

    CGEventPost(kCGHIDEventTap, eventRef);

    CFRelease(eventRef);
}

auto tapCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
                 void *refcon) -> CGEventRef {
    const Event newEvent{Key::A, true};
    auto *self{static_cast<MacOS *>(refcon)};

    self->sendEventToCore(newEvent);

    return event;
}

auto MacOS::run() -> void {
    CGEventMask eventMask{CGEventMaskBit(kCGEventKeyDown) |
                          // CGEventMaskBit(kCGEventKeyUp) |
                          CGEventMaskBit(kCGEventFlagsChanged)};

    CFMachPortRef machPortRef{CGEventTapCreate(
        kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
        eventMask, tapCallback, this)};

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
