#include <dispatch.hpp>
#include <keys.hpp>
#include <macos.hpp>
#include <transform.hpp>

namespace mac::input::dispatch {
namespace set = mac::input::transform;
auto containingRegulars(MacOS *self, const comb::Combination &combination)
    -> void {
    const auto [regularsArray, regularsCount]{combination.getRegulars()};
    const auto modifiers{combination.getModifiers()};

    auto *event{CGEventCreateKeyboardEvent(nullptr, 0, false)};

    for (size_t i{0}; i != regularsCount; ++i) {
        const auto regular{regularsArray.at(i)};
        const auto nativeCode{self->keyToNativeCode(regular)};

        if (!nativeCode.has_value()) {
            // TODO
        }

        set::eventToFields(self, event, nativeCode.value(), modifiers, true,
                           mac::consts::kSyntheticTag);
        set::eventToFields(self, event, nativeCode.value(), modifiers, false,
                           mac::consts::kSyntheticTag);
    }

    CFRelease(event);
}
} // namespace mac::input::dispatch
