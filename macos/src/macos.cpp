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
        modifierBitMask |= modifierToCGEventFlags(modifiersArray.at(i));
    }

    CGEventSetFlags(event, modifierBitMask);
}

auto mac::MacOS::setCurrentCombinationToCurrentNativeCode() -> void {
    const auto currentNative{getCurrentNativeCode()};

    const auto combination{comb::Combination(
        {.array = {nativeCodeToKey(currentNative)}, .count = 1})};

    setCurrentCombination(combination);
}

auto mac::MacOS::setEventToCurrentCombination(Event &event) const -> void {
    const auto currentCombination{getCurrentCombination()};

    setEventFlagsToModifiers(event, currentCombination.getModifiers());

    const auto [regularsArray, regularsCount]{currentCombination.getRegulars()};

    const auto config{getConfig()};

    // TODO This doesn't support multi-key combinations
    for (size_t i{0}; i != regularsCount; ++i) {
        CGEventSetIntegerValueField(
            event, kCGKeyboardEventKeycode,
            config.keyToNativeCode.at(regularsArray.at(i)));
    }
}

[[nodiscard]] auto mac::MacOS::modifierToCGEventFlags(key::Keys modifier) const
    -> CGEventFlags {

    if (!key::isModifier(modifier)) {
        // TODO
        return 0;
    }

    const auto &config{getConfig()};

    // TODO bound check
    return config.modifierToCGEventFlags.at(modifier);
}

auto mac::MacOS::setCurrentNativeCode(NativeCode nativeCode) -> void {
    m_currentNativeCode = nativeCode;
}

auto mac::MacOS::setCurrentCombination(const comb::Combination &combination)
    -> void {
    m_currentCombination = combination;
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

[[nodiscard]] auto mac::MacOS::getCurrentCombination() const
    -> comb::Combination {
    return m_currentCombination;
}

[[nodiscard]] auto mac::MacOS::getBindedCombination() const
    -> comb::Combination {
    const auto nativeCode{getCurrentNativeCode()};
    const auto key{nativeCodeToKey(nativeCode)};

    return getKeyBinding(nativeCodeToKey(nativeCode));
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
