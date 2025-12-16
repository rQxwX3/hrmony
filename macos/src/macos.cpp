#include <macos.hpp>
#include <macosConstants.hpp>
#include <types.hpp>

#include <ApplicationServices/ApplicationServices.h>

auto MacOS::setEventModifiersToCurrent(Event &event) -> void {
    const auto currentModifiers{getCurrentModifiers()};

    NativeModifier modifierBitMask{0};

    for (const auto &modifier : currentModifiers) {
        if (modifier == Keys::Modifiers::NULLKEY) {
            continue;
        }

        modifierBitMask |= modifier2NativeModifier(modifier);
    }

    CGEventSetFlags(event, modifierBitMask);
}

auto processKeyPress(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
                     void *refcon) -> CGEventRef {
    auto *self{static_cast<MacOS *>(refcon)};

    if (!self->isHRMMode()) {
        return event;
    }

    const auto nativeKey{static_cast<NativeKeyCode>(
        CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode))};

    const auto modifier{
        self->getKeyBinding(self->nativeKey2Printable(nativeKey))};

    if (Keys::Modifiers::NULLKEY == modifier) {
        self->setEventModifiersToCurrent(event);
        self->resetCurrentModifiers();

        return event;
    }

    self->addCurrentModifier(modifier);
    return nullptr;
}

MacOS::MacOS(App *appPtr)
    : Platform(MacOSConstants::nativeKey2Printable,
               MacOSConstants::modifier2NativeModifier, appPtr) {
    CGEventMask eventMask{CGEventMaskBit(kCGEventKeyDown) |
                          // CGEventMaskBit(kCGEventKeyUp) |
                          CGEventMaskBit(kCGEventFlagsChanged)};

    CFMachPortRef machPortRef{CGEventTapCreate(
        kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
        eventMask, processKeyPress, this)};

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
