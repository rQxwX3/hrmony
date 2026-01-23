#include <keys.hpp>
#include <macos.hpp>
#include <transform.hpp>

namespace mac::input::transform {
namespace set = mac::input::transform;
auto eventFlagsToModifiers(const MacOS *self, Event &event,
                           comb::types::Modifiers modifiers) -> void {
    const auto [modifiersArray, modifiersCount]{modifiers};

    NativeModifier modifierBitMask{0};

    for (size_t i{0}; i != modifiersCount; ++i) {
        const auto cgEventFlags{
            self->modifierToCGEventFlags(modifiersArray.at(i))};

        if (!cgEventFlags.has_value()) {
            // TODO
        }

        modifierBitMask |= *cgEventFlags;
    }

    CGEventSetFlags(event, modifierBitMask);
} // namespace mac::input::transform

auto eventToCombination(const MacOS *self, Event &event,
                        const comb::Combination &combination) -> void {
    eventFlagsToModifiers(self, event, combination.getModifiers());

    const auto [regularsArray, regularsCount]{combination.getRegulars()};

    const auto config{self->getConfig()};

    // TODO This doesn't support multi-key
    // combinations, and it shouldn't
    for (size_t i{0}; i != regularsCount; ++i) {
        const auto nativeCode{config.keyToNativeCode.at(regularsArray.at(i))};

        if (!nativeCode.has_value()) {
            // TODO
        }

        CGEventSetIntegerValueField(event, kCGKeyboardEventKeycode,
                                    nativeCode.value());
    }
}

auto eventToFields(const MacOS *self, Event &event, const NativeCode nativeCode,
                   const comb::types::Modifiers modifiers, const bool isDown,
                   const int64_t kSyntheticTag) -> void {
    CGEventSetIntegerValueField(event, kCGKeyboardEventKeycode, nativeCode);
    eventFlagsToModifiers(self, event, modifiers);

    CGEventSetIntegerValueField(event, kCGEventSourceUserData, kSyntheticTag);
    CGEventSetType(event, (isDown) ? kCGEventKeyDown : kCGEventKeyUp);

    CGEventPost(kCGHIDEventTap, event);
}
} // namespace mac::input::transform
