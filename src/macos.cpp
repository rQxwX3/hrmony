#include "../include/macos.hpp"

#include <ApplicationServices/ApplicationServices.h>
#include <chrono>
#include <iostream>

auto tapCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
                 void *refcon) -> CGEventRef {

    auto start{std::chrono::high_resolution_clock::now()};

    auto *self{static_cast<MacOS *>(refcon)};

    if (!self->isHRMMode()) {
        auto end1{std::chrono::high_resolution_clock::now()};
        std::chrono::duration<double> elapsed = end1 - start;
        // std::cout << elapsed.count() << '\n';
        return event;
    }

    const auto &eventNativeKeyCode{static_cast<CGKeyCode>(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode))};

    self->sendEventToApp({{MacOS::native2Key(eventNativeKeyCode)}});

    // TODO return nullptr (Core should send back the remapped event)
    return nullptr;
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
}

auto MacOS::run() -> void { CFRunLoopRun(); }

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
