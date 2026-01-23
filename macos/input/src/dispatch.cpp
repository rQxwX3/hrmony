#include <dispatch.hpp>
#include <keys.hpp>
#include <macos.hpp>
#include <transform.hpp>

namespace mac::input::dispatch {
namespace set = mac::input::transform;

auto multipleRegulars(MacOS *self, const comb::Combination &combination)
    -> void {
    const auto [regularsArray, regularsCount]{combination.getRegulars()};
    const auto modifiers{combination.getModifiers()};

    auto *event{CGEventCreateKeyboardEvent(nullptr, 0, false)};
    CGEventSetIntegerValueField(event, kCGEventSourceUserData,
                                mac::consts::kSyntheticTag);
    set::eventFlagsToModifiers(self, event, modifiers);

    for (size_t i{0}; i != regularsCount; ++i) {
        const auto regular{regularsArray.at(i)};
        const auto nativeCode{self->keyToNativeCode(regular)};

        if (!nativeCode.has_value()) {
            // TODO
        }

        CGEventSetIntegerValueField(event, kCGKeyboardEventKeycode,
                                    nativeCode.value());

        // Key down event
        CGEventSetType(event, kCGEventKeyDown);
        CGEventPost(kCGHIDEventTap, event);

        // Key up event
        CGEventSetType(event, kCGEventKeyUp);
        CGEventPost(kCGHIDEventTap, event);
    }

    CFRelease(event);
}
} // namespace mac::input::dispatch
