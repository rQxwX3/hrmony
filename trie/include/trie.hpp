#ifndef TRIE_HPP
#define TRIE_HPP

#include "node.hpp"

#include <memory>
#include <string_view>

class Trie {
  private:
    std::unique_ptr<Node> m_root{nullptr};

  public:
    Trie();

    auto insertString(std::string_view stringView) -> void;

    auto findString(std::string_view stringView) -> bool;
};

#endif // TRIE_HPP
