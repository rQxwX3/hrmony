#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <macos.hpp>
#include <types.hpp>

namespace macOS::util {
[[nodiscard]] auto getBindedCombination(const MacOS *self) -> Combination;

[[nodiscard]] auto isHRMModeEnterTriggered(const MacOS *self) -> bool;

[[nodiscard]] auto isHRMModeExitTriggered(const MacOS *self) -> bool;

[[nodiscard]] auto isKeymapFinished(const MacOS *self) -> bool;

[[nodiscard]] auto isBindedKeyPressed(const MacOS *self) -> bool;

[[nodiscard]] auto processKeyPress(CGEventTapProxy proxy, CGEventType type,
                                   CGEventRef event, void *refcon)
    -> CGEventRef;

[[nodiscard]] auto isProcessingLeaderUp(const MacOS *self) -> bool;

auto addKeyToFinishedKeymap(MacOS *self) -> void;

} // namespace macOS::util

#endif // UTILITY_HPP
