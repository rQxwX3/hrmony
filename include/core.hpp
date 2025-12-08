#ifndef CORE_HPP
#define CORE_HPP

#include "types.hpp"
#include <unordered_map>

class App;

class Core {
  private:
    App *m_appPtr{nullptr};
    std::unordered_map<Key, std::vector<Key>> m_keyMaps;

  public:
    Core(App *appPtr);

    auto onPlatformEvent(const Event &event) -> void;
};

#endif // CORE_HPP
