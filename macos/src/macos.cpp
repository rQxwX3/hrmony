#include <app.hpp>
#include <constants.hpp>
#include <macos.hpp>
#include <utility.hpp>

#include <ApplicationServices/ApplicationServices.h>

auto mac::MacOS::setEventFlagsToModifiers(
    Event &event, comb::types::Modifiers modifiers) const -> void {
    const auto [modifiersArray, modifiersCount]{modifiers};

    NativeModifier modifierBitMask{0};

    for (size_t i{0}; i != modifiersCount; ++i) {
        const auto cgEventFlags{modifierToCGEventFlags(modifiersArray.at(i))};

        if (!cgEventFlags.has_value()) {
            // TODO
        }

        modifierBitMask |= *cgEventFlags;
    }

    CGEventSetFlags(event, modifierBitMask);
}

auto mac::MacOS::setEventToCombination(
    Event &event, const comb::Combination &combination) const -> void {
    setEventFlagsToModifiers(event, combination.getModifiers());

    const auto [regularsArray, regularsCount]{combination.getRegulars()};

    const auto config{getConfig()};

    // TODO This doesn't support multi-key
    // combinations, and it shouldn't
    for (size_t i{0}; i != regularsCount; ++i) {
        CGEventSetIntegerValueField(
            event, kCGKeyboardEventKeycode,
            config.keyToNativeCode.at(regularsArray.at(i)));
    }
}

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

[[nodiscard]] auto mac::MacOS::nativeCodeToKey(NativeCode nativeCode) const
    -> key::Keys {
    const auto config{getConfig()};

    // TODO bound check
    return config.nativeCodeToKey.at(nativeCode);
}
[[nodiscard]] auto mac::MacOS::keyToNativeCode(key::Keys key) const
    -> NativeCode {
    const auto config{getConfig()};

    return config.keyToNativeCode.at(key);
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
