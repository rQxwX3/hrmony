#include "../include/node.hpp"

#include <memory>

auto Node::isTerminal() const -> bool { return m_terminal; }

auto Node::markTerminal() -> void { m_terminal = true; }

auto Node::at(const unsigned char i) -> Node * {
    return m_children.at(i).get();
}

auto Node::ensureChild(const unsigned char i) -> void {
    if (nullptr == m_children.at(i)) {
        m_children.at(i) = std::make_unique<Node>();
    }
}
