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
}

auto eventToSingleRegularCombination(const MacOS *self, Event &event,
                                     const comb::Combination &combination)
    -> void {
    eventFlagsToModifiers(self, event, combination.getModifiers());

    const auto [regularsArray, regularsCount]{combination.getRegulars()};
    const auto nativeCode{self->keyToNativeCode(regularsArray[0])};

    if (!nativeCode.has_value()) {
        // TODO
    }

    CGEventSetIntegerValueField(event, kCGKeyboardEventKeycode,
                                nativeCode.value());
}
} // namespace mac::input::transform
