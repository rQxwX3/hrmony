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

[[nodiscard]] auto getGroupAction(const mac::MacOS *self)
    -> const grp::types::Action &;

[[nodiscard]] auto isGroupExitTriggered(const mac::MacOS *self) -> bool;

[[nodiscard]] auto isKeymapFinished(const mac::MacOS *self,
                                    const comb::Combination &combination)
    -> bool;

[[nodiscard]] auto isKeymapInProgress(const mac::MacOS *self,
                                      const comb::Combination &combination)
    -> bool;

[[nodiscard]] auto processKeyPress(CGEventTapProxy proxy, CGEventType type,
                                   CGEventRef event, void *refcon)
    -> CGEventRef;

[[nodiscard]] auto isProcessingLeaderUp(const mac::MacOS *self) -> bool;

auto sendMultipleRegulars(MacOS *self, const comb::Combination &combination)
    -> void;

auto processKeymapInProgress(MacOS *self, Event &event,
                             const comb::Combination &combination) -> void;

auto processFinishedKeymap(MacOS *self, Event &event,
                           const comb::Combination &combination) -> void;

auto processNoModifiersBinding(MacOS *self, Event &event,
                               const comb::Combination &binding) -> void;

auto processEmptyBinding(MacOS *self, Event &event,
                         const comb::Combination &binding) -> void;

auto processMultipleRegularsBinding(MacOS *self,
                                    const comb::Combination &combination)
    -> void;

auto processSingleCombinationBinding(MacOS *self, Event &event,
                                     const grp::types::Combinations &binding)
    -> void;

auto processMultipleCombinationsBinding(MacOS *self, Event &event,
                                        const grp::types::Combinations &binding)
    -> void;
} // namespace mac::util

#endif // UTILITY_HPP
