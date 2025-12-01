#include "../include/trie.hpp"

#include <memory>
#include <string_view>

Trie::Trie() { m_root = std::make_unique<Node>(); }

auto Trie::insertString(std::string_view stringView) -> void {
    auto *currNode = m_root.get();

    for (const unsigned char svChar : stringView) {
        currNode->ensureChild(svChar);

        currNode = currNode->at(svChar);
    }

    currNode->markTerminal();
}

auto Trie::findString(std::string_view stringView) -> bool {
    auto *currNode = m_root.get();

    for (const unsigned char svChar : stringView) {
        auto *childNode = currNode->at(svChar);

        if (nullptr == childNode) {
            return false;
        }

        currNode = childNode;
    }

    return true;
}
