#include <keys.hpp>
#include <macos.hpp>
#include <validate.hpp>

namespace mac::input::validate {
[[nodiscard]] auto groupExitTriggered(const MacOS *self) -> bool {
    const auto exitKey{self->getConfig().exitKey};
    const auto nativeCode{self->getCurrentNativeCode()};

    const auto key{self->nativeCodeToKey(nativeCode)};

    if (!key.has_value()) {
        // TODO
    }

    return key == exitKey;
}

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
