#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <combination.hpp>
#include <macos.hpp>

namespace mac::util {
auto createAndPostKeyboardEvent(const mac::MacOS *self, NativeCode nativeCode,
                                comb::types::Modifiers modifiers, bool isDown)
    -> void;

[[nodiscard]] auto isHRMModeEnterTriggered(const mac::MacOS *self) -> bool;

[[nodiscard]] auto isHRMModeExitTriggered(const mac::MacOS *self) -> bool;

[[nodiscard]] auto isKeymapFinished(const mac::MacOS *self) -> bool;

[[nodiscard]] auto isBindedKeyPressed(const mac::MacOS *self) -> bool;

[[nodiscard]] auto processKeyPress(CGEventTapProxy proxy, CGEventType type,
                                   CGEventRef event, void *refcon)
    -> CGEventRef;

[[nodiscard]] auto isProcessingLeaderUp(const mac::MacOS *self) -> bool;

auto addKeyToFinishedKeymap(mac::MacOS *self) -> void;

} // namespace mac::util

#endif // UTILITY_HPP
