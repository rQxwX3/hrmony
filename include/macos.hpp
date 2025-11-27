#ifndef MACOS_HPP
#define MACOS_HPP

#include "event.hpp"
#include "iplatform.hpp"
#include "key.hpp"

#include <CoreGraphics/CoreGraphics.h>
#include <unordered_map>

class MacOS : public IPlatform {
  private:
    std::unordered_map<Key, CGKeyCode> m_keyCodeMap;

  public:
    MacOS();

    [[nodiscard]] auto convertKey(const Key &k) const -> CGKeyCode;
    auto sendEvent(const Event &e) -> void;
};

#endif // MACOS_HPP
