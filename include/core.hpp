#ifndef CORE_HPP
#define CORE_HPP

#include "types.hpp"
#include <unordered_map>

class App;

class Core {
  private:
    App *m_appPtr;
    std::unordered_map<Key, std::vector<Key>> m_keyMaps;

  private:
    auto getRemappedKeys(Key key) -> std::vector<Key>;

  public:
    Core(App *appPtr = nullptr);

    auto onPlatformEvent(const Event &event) -> void;
};

#endif // CORE_HPP
