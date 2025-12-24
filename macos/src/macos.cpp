#include <app.hpp>
#include <constants.hpp>
#include <macos.hpp>
#include <types.hpp>
#include <utility.hpp>

#include <ApplicationServices/ApplicationServices.h>

using macOS::MacOS;

auto MacOS::setEventToCurrentCombination(Event &event) -> void {
    const auto currentCombination{getCurrentCombination()};

    const auto currentModifiers{currentCombination.getModifiers()};
    NativeModifier modifierBitMask{0};

    for (const auto &modifier : currentModifiers) {
        if (modifier == Keys::Modifiers::NULLKEY) {
            continue;
        }

        modifierBitMask |= modifier2NativeModifier(modifier);
    }

    const auto currentKey{currentCombination.getKeys().at(0)};

    const auto config{getConfig()};

    CGEventSetIntegerValueField(
        event, kCGKeyboardEventKeycode,
        config.printable2NativeKey.at(static_cast<size_t>(currentKey)));

    CGEventSetFlags(event, modifierBitMask);
}

[[nodiscard]] auto MacOS::isLeaderUpProcessed() const -> bool {
    return m_leaderUpProcessed;
}

auto MacOS::toggleLeaderUpProcessed() -> void {
    m_leaderUpProcessed = !m_leaderUpProcessed;
}

MacOS::MacOS(App *appPtr) : Platform(appPtr), m_leaderUpProcessed{false} {
    CGEventMask eventMask{CGEventMaskBit(kCGEventKeyDown) |
                          // CGEventMaskBit(kCGEventKeyUp) |
                          CGEventMaskBit(kCGEventFlagsChanged)};

    CFMachPortRef machPortRef{CGEventTapCreate(
        kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
        eventMask, macOS::util::processKeyPress, this)};

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
