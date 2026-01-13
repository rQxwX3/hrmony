#include <app.hpp>
#include <constants.hpp>
#include <macos.hpp>
#include <utility.hpp>

#include <ApplicationServices/ApplicationServices.h>

[[nodiscard]] auto mac::MacOS::modifierToCGEventFlags(key::Keys modifier) const
    -> std::optional<CGEventFlags> {

    if (!key::isModifier(modifier)) {
        return {};
    }

    const auto &config{getConfig()};

    return config.modifierToCGEventFlags.at(modifier);
}

auto mac::MacOS::setCurrentNativeCode(NativeCode nativeCode) -> void {
    m_currentNativeCode = nativeCode;
}

[[nodiscard]] auto mac::MacOS::getCurrentNativeCode() const -> NativeCode {
    return m_currentNativeCode;
}

[[nodiscard]] auto mac::MacOS::isLeaderUpProcessed() const -> bool {
    return m_leaderUpProcessed;
}

auto mac::MacOS::toggleLeaderUpProcessed() -> void {
    m_leaderUpProcessed = !m_leaderUpProcessed;
}

mac::MacOS::MacOS(grp::Group *groupPtr, app::App *appPtr)
    : Platform(groupPtr, appPtr), m_leaderUpProcessed{false},
      m_currentNativeCode{0} {
    CGEventMask eventMask{CGEventMaskBit(kCGEventKeyDown) |
                          // CGEventMaskBit(kCGEventKeyUp) |
                          CGEventMaskBit(kCGEventFlagsChanged)};

    CFMachPortRef machPortRef{CGEventTapCreate(
        kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
        eventMask, mac::util::processKeyPress, this)};

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

auto mac::MacOS::run() -> void { CFRunLoopRun(); }

mac::MacOS::~MacOS() {
    CFRunLoopStop(m_runLoopRef);
    CFRelease(m_runLoopRef);
}
