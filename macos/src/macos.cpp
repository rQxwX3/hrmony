#include <app.hpp>
#include <constants.hpp>
#include <macos.hpp>
#include <utility.hpp>

#include <ApplicationServices/ApplicationServices.h>

auto mac::MacOS::setEventToCurrentCombination(Event &event) -> void {
    const auto currentCombination{getCurrentCombination()};

    const auto currentModifiers{currentCombination.getModifiers()};
    const auto currentModifiersCount{currentCombination.getModifiersCount()};

    NativeModifier modifierBitMask{0};

    for (size_t i{0}; i != currentModifiersCount; ++i) {
        modifierBitMask |= modifierToCGEventFlags(currentModifiers.at(i));
    }

    CGEventSetFlags(event, modifierBitMask);

    const auto currentRegulars{currentCombination.getRegulars()};
    const auto currentRegularsCount{currentCombination.getRegularsCount()};

    const auto config{getConfig()};

    // TODO This doesn't support multi-key combinations
    for (size_t i{0}; i != currentRegularsCount; ++i) {
        CGEventSetIntegerValueField(
            event, kCGKeyboardEventKeycode,
            config.keyToNativeCode.at(currentRegulars.at(i)));
    }
}

[[nodiscard]] auto mac::MacOS::modifierToCGEventFlags(key::Keys modifier) const
    -> CGEventFlags {

    if (!key::isModifier(modifier)) {
        // TODO
        return 0;
    }

    const auto &config{getConfig()};

    return config.modifierToCGEventFlags.at(modifier);
}

auto mac::MacOS::setCurrentNativeCode(NativeCode nativeCode) -> void {
    m_currentNativeCode = nativeCode;
}

[[nodiscard]] auto mac::MacOS::nativeCodeToKey(NativeCode nativeCode) const
    -> key::Keys {
    const auto config{getConfig()};

    return config.nativeCodeToKey.at(nativeCode);
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

mac::MacOS::MacOS(app::App *appPtr)
    : Platform(appPtr), m_leaderUpProcessed{false}, m_currentNativeCode{0} {
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
