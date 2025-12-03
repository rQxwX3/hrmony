#include "../include/macos.hpp"

#include <ApplicationServices/ApplicationServices.h>
#include <iostream>

MacOS::MacOS(const App *app) {
    MacOS::sApp = app;

    MacOS::setEventCallback([](const Event &event) -> void {
        if (event.getKey() == Key::A) {
            std::cout << "A was hit\n";
        }
    });
}

auto MacOS::tapCallback(CGEventTapProxy proxy, CGEventType type,
                        CGEventRef event, void *refcon) -> CGEventRef {
    splatformToCore({Key::A, true});
    return event;
}

auto MacOS::run() -> void {
    CGEventMask eventMask{CGEventMaskBit(kCGEventKeyDown) |
                          // CGEventMaskBit(kCGEventKeyUp) |
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

auto MacOS::postEventToOS(const Event &event) -> void {
    CGEventRef eventRef{CGEventCreateKeyboardEvent(
        nullptr, key2Native(event.getKey()), event.isDown())};

    CGEventPost(kCGHIDEventTap, eventRef);

    CFRelease(eventRef);
}
