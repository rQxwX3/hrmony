#include <app.hpp>
#include <constants.hpp>
#include <macos.hpp>
#include <process.hpp>

#include <ApplicationServices/ApplicationServices.h>

namespace mac {
[[nodiscard]] auto MacOS::modifierToCGEventFlags(key::Keys modifier) const
    -> std::optional<CGEventFlags> {

    if (!key::isModifier(modifier)) {
        return {};
    }

    const auto &config{getConfig()};

    return config.modifierToCGEventFlags.at(modifier);
}

MacOS::MacOS(grp::Group *groupPtr, app::App *appPtr)
    : Platform(groupPtr, appPtr) {
    CGEventMask eventMask{CGEventMaskBit(kCGEventKeyDown) |
                          // CGEventMaskBit(kCGEventKeyUp) |
                          CGEventMaskBit(kCGEventFlagsChanged)};

    CFMachPortRef machPortRef{CGEventTapCreate(
        kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
        eventMask, mac::input::process::keyPress, this)};

    if (nullptr == machPortRef) {
        // TODO
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
} // namespace mac
