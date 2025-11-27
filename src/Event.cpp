#include "../include/event.hpp"

[[nodiscard]] auto Event::getKey() const -> Key { return m_key; }
[[nodiscard]] auto Event::isDown() const -> bool { return m_down; }
