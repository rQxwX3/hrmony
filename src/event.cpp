#include "../include/event.hpp"

Event::Event(Key key, bool down) : m_key{key}, m_down{down} {};

[[nodiscard]] auto Event::getKey() const -> Key { return m_key; }

[[nodiscard]] auto Event::isDown() const -> bool { return m_down; }
