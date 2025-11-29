#ifndef MACOS_HPP
#define MACOS_HPP

#include "baseplatform.hpp"
#include "event.hpp"
#include "key.hpp"
#include "types.hpp"

#include <CoreGraphics/CoreGraphics.h>
#include <unordered_map>

class MacOS : public BasePlatform {
  private:
    std::unordered_map<Key, CGKeyCode> m_keyCodeMap;

    auto startListening() -> void override;

    [[nodiscard]] static auto tapCallback(CGEventTapProxy proxy,
                                          CGEventType type, CGEventRef event,
                                          void *refcon) -> CGEventRef;

  public:
    MacOS(const HRMModeToggleCallback &callback);

    [[nodiscard]] auto convertKey(const Key &k) const -> CGKeyCode;
    auto sendEvent(const Event &e) -> void override;
};

#endif // MACOS_HPP
