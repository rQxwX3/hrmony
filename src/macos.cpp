#include "../include/macos.hpp"

#include <ApplicationServices/ApplicationServices.h>

auto tapCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
                 void *refcon) -> CGEventRef {
    auto *self{static_cast<MacOS *>(refcon)};

    const auto &eventNativeKeyCode{static_cast<CGKeyCode>(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode))};

    self->sendEventToCore({{MacOS::native2Key(eventNativeKeyCode)}});

    if (MacOS::native2Key(eventNativeKeyCode) == Key::A) {
        return nullptr;
    }

    return event;
}

MacOS::MacOS(App *appPtr) : Platform(appPtr) {
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

    m_runLoopRef = CFRunLoopGetCurrent();
    CFRetain(m_runLoopRef);

    CFRunLoopAddSource(m_runLoopRef, runLoopSourceRef, kCFRunLoopCommonModes);

    CGEventTapEnable(machPortRef, true);
    CFRunLoopRun();
}

MacOS::~MacOS() {
    CFRunLoopStop(m_runLoopRef);
    CFRelease(m_runLoopRef);
}

auto MacOS::postEventToOS(const Event &event) -> void {
    const std::vector<Key> &eventKeys{event.getKeys()};

    for (const auto &key : eventKeys) {
        CGEventRef eventRef{
            CGEventCreateKeyboardEvent(nullptr, key2Native(key), true)};

        CGEventPost(kCGHIDEventTap, eventRef);

        CFRelease(eventRef);
    }
}
