#include "../include/macos.hpp"
#include "../include/macosDefaults.hpp"

#include <ApplicationServices/ApplicationServices.h>

auto tapCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
                 void *refcon) -> CGEventRef {
    auto *self{static_cast<MacOS *>(refcon)};

    if (!self->isHRMMode()) {
        return event;
    }

    const auto &nativeKey{static_cast<CGKeyCode>(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode))};

    const auto modifier{
        self->getKeyBinding(self->nativeKey2Printable(nativeKey))};

    if (modifier == Keys::Modifiers::NULLKEY) {
        return event;
    }

    CGEventSetFlags(event, self->modifier2NativeModifier(modifier));

    return event;
}

MacOS::MacOS(App *appPtr)
    : Platform(MacOSDefaults::nativeKey2Printable,
               MacOSDefaults::modifier2NativeModifier, appPtr) {
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

// auto MacOS::postEventToOS(const Event &event) -> void {
//     const std::vector<Key> &eventKeys{event.getKeys()};
//
//     for (const auto &key : eventKeys) {
//         CGEventRef eventRef{
//             CGEventCreateKeyboardEvent(nullptr, key2Native(key), true)};
//
//         CGEventPost(kCGHIDEventTap, eventRef);
//
//         CFRelease(eventRef);
//     }
// }
