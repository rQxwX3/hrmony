#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <macos.hpp>
#include <types.hpp>

namespace macOS::util {
auto isModifiersArrayEmpty(const ModifiersArray &modifiersArray) -> bool;

auto getBindedModifiers(const MacOS *self, const Event &event)
    -> ModifiersArray;

auto isHRMModeEnterTriggered(const MacOS *self, const Event &event) -> bool;

auto isKeymapFinished(const MacOS *self, const Event &event) -> bool;

auto isBindedKeyPressed(const MacOS *self, const Event &event) -> bool;

auto processKeyPress(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
                     void *refcon) -> CGEventRef;
} // namespace macOS::util

#endif // UTILITY_HPP
