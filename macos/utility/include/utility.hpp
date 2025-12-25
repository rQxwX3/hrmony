#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <macos.hpp>
#include <types.hpp>

namespace macOS::util {
auto getBindedCombination(const MacOS *self, const Event &event) -> Combination;

auto isHRMModeEnterTriggered(const MacOS *self) -> bool;

auto isHRMModeExitTriggered(const MacOS *self) -> bool;

auto isKeymapFinished(const MacOS *self) -> bool;

auto isBindedKeyPressed(const MacOS *self) -> bool;

auto processKeyPress(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
                     void *refcon) -> CGEventRef;

auto addKeyToFinishedKeymap(MacOS *self) -> void;
} // namespace macOS::util

#endif // UTILITY_HPP
