#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <macos.hpp>
#include <types.hpp>

namespace macOS::util {
auto getBindedModifier(const MacOS *self, const Event &event)
    -> Keys::Modifiers;

auto isHRMModeEnterTriggered(const MacOS *self, const Event &event) -> bool;

auto isKeymapFinished(const MacOS *self, const Event &event) -> bool;

auto isBindedKeyPressed(const MacOS *self, const Event &event) -> bool;

auto processKeyPress(CGEventTapProxy proxy, CGEventType type, CGEventRef event,
                     void *refcon) -> CGEventRef;
} // namespace macOS::util

#endif // UTILITY_HPP
