#ifndef EVENT_HPP
#define EVENT_HPP

#include "key.hpp"

#include <vector>

class Event {
  private:
    std::vector<Key> m_keys;

  public:
    Event();
    Event(const std::vector<Key> &keys);

    [[nodiscard]] auto getKeys() const -> const std::vector<Key> &;
};

#endif // EVENT_HPP
