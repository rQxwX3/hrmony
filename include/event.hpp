#ifndef EVENT_HPP
#define EVENT_HPP

#include "key.hpp"

class Event {
  private:
    Key m_key;
    bool m_down;

  public:
    Event(Key key, bool down);

    [[nodiscard]] auto getKey() const -> Key;
    [[nodiscard]] auto isDown() const -> bool;
};

#endif // EVENT_HPP
