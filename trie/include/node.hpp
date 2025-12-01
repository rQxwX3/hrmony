#ifndef NODE_HPP
#define NODE_HPP

#define MAX_CHILDREN 256

#include <array>
#include <memory>

class Node {
  private:
    bool m_terminal{false};
    std::array<std::unique_ptr<Node>, MAX_CHILDREN> m_children{nullptr};

  public:
    Node() = default;

    [[nodiscard]] auto isTerminal() const -> bool;

    auto markTerminal() -> void;

    auto at(unsigned char i) -> Node *;

    auto ensureChild(unsigned char i) -> void;
};

#endif // NODE_HPP
