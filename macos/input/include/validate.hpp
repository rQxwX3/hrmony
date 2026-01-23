#ifndef INPUT_VALIDATE_HPP
#define INPUT_VALIDATE_HPP

#include <combination.hpp>
#include <macos.hpp>

namespace mac::input::validate {
using key::Keys;
using mac::MacOS, mac::types::Event, mac::types::NativeModifier;

[[nodiscard]] auto groupExitTriggered(const MacOS *self) -> bool;

[[nodiscard]] auto inputInProgress(const MacOS *self,
                                   const comb::Combination &combination)
    -> bool;

[[nodiscard]] auto syntheticEvent(const Event &event) -> bool;

[[nodiscard]] auto processingLeaderUp(const MacOS *self) -> bool;
} // namespace mac::input::validate

#endif // INPUT_VALIDATE_HPP
