#include "../include/event.hpp"

Event::Event() = default;

Event::Event(const std::vector<Key> &keys) : m_keys{keys} {};

[[nodiscard]] auto Event::getKeys() const -> const std::vector<Key> & {
    return m_keys;
}
