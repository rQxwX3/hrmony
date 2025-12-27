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
    const auto currentModifiersCount{currentCombination.getModifiersCount()};

    NativeModifier modifierBitMask{0};

    for (size_t i{0}; i != currentModifiersCount; ++i) {
        modifierBitMask |= modifierToNativeModifier(currentModifiers.at(i));
    }

    CGEventSetFlags(event, modifierBitMask);

    const auto currentKeys{currentCombination.getKeys()};
    const auto currentKeysCount{currentCombination.getKeysCount()};

    const auto config{getConfig()};

    for (size_t i{0}; i != currentKeysCount; ++i) {
        // TODO This doesn't support multi-key combinations
        CGEventSetIntegerValueField(
            event, kCGKeyboardEventKeycode,
            config.keyToNativeCode.at(currentKeys.at(i)));
    }
}

[[nodiscard]] auto MacOS::modifierToCGEventFlags(key::Modifiers modifier) const
    -> CGEventFlags {
    const auto &config{getConfig()};

    return config.modifierToCGEventFlags.at(modifier);
}

[[nodiscard]] auto
MacOS::nativeCodeToModifier(NativeModifier nativeModifier) const
    -> key::Modifiers {
    const auto &config{getConfig()};

    return config.nativeCodeToModifier.at(nativeModifier);
}

auto MacOS::setCurrentBindedCombination(const Combination &combination)
    -> void {
    m_currentBindedCombination = combination;
}

auto MacOS::setCurrentNativeCode(NativeKeyCode nativeCode) -> void {
    m_currentNativeCode = nativeCode;
}

[[nodiscard]] auto MacOS::getCurrentBindedCombination() const -> Combination {
    return m_currentBindedCombination;
}

[[nodiscard]] auto MacOS::getCurrentNativeCode() const -> NativeKeyCode {
    return m_currentNativeCode;
}

[[nodiscard]] auto MacOS::isLeaderUpProcessed() const -> bool {
    return m_leaderUpProcessed;
}

auto MacOS::toggleLeaderUpProcessed() -> void {
    m_leaderUpProcessed = !m_leaderUpProcessed;
}

MacOS::MacOS(App *appPtr)
    : Platform(appPtr), m_leaderUpProcessed{false}, m_currentNativeCode{0} {
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
