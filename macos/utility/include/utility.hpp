#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <combination.hpp>
#include <macos.hpp>

namespace mac::util {
constexpr int64_t kSyntheticTag{0xC0FFEE};

auto createAndPostKeyboardEvent(const mac::MacOS *self, NativeCode nativeCode,
                                comb::types::Modifiers modifiers, bool isDown,
                                int64_t kSyntheticTag = 0) -> void;

[[nodiscard]] auto createCombinationFromNativeCode(const mac::MacOS *self,
                                                   NativeCode nativeCode)
    -> comb::Combination;

[[nodiscard]] auto isSyntheticEvent(const Event &event) -> bool;

[[nodiscard]] auto isHRMModeEnterTriggered(const mac::MacOS *self) -> bool;

[[nodiscard]] auto isHRMModeExitTriggered(const mac::MacOS *self) -> bool;

[[nodiscard]] auto isKeymapFinished(const mac::MacOS *self) -> bool;

[[nodiscard]] auto isBindedKeyPressed(const mac::MacOS *self) -> bool;

[[nodiscard]] auto processKeyPress(CGEventTapProxy proxy, CGEventType type,
                                   CGEventRef event, void *refcon)
    -> CGEventRef;

[[nodiscard]] auto isProcessingLeaderUp(const mac::MacOS *self) -> bool;

} // namespace mac::util

#endif // UTILITY_HPP
