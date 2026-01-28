#include <keys.hpp>
#include <macos.hpp>
#include <validate.hpp>

namespace mac::input::validate {
[[nodiscard]] auto inputInProgress(const MacOS *self,
                                   const comb::Combination &combination)
    -> bool {
    return combination.containsNoRegulars() &&
           !combination.containsNoModifiers();
}

[[nodiscard]] auto syntheticEvent(const Event &event) -> bool {
    return CGEventGetIntegerValueField(event, kCGEventSourceUserData) ==
           mac::consts::kSyntheticTag;
}
} // namespace mac::input::validate
