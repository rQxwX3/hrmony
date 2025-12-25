#include <combination.hpp>

Combination::Combination()
    : m_modifiers{}, m_keys{}, m_modifiersCount{0}, m_keysCount{0} {}

Combination::Combination(const CombinationModifiers &modifiers,
                         size_t modifiersCount)
    : Combination() {
    if (modifiersCount > m_modifiers.size()) {
        // TODO
    }

    for (int i{0}; i != modifiersCount; ++i) {
        m_modifiers[i] = modifiers[i];
        ++m_modifiersCount;
    }
}

Combination::Combination(const CombinationKeys &keys, size_t keysCount)
    : Combination() {
    if (keysCount > m_keys.size()) {
        // TODO
    }

    for (int i{0}; i != keysCount; ++i) {
        m_keys[i] = keys[i];
        ++m_keysCount;
    }
}

Combination::Combination(const CombinationModifiers &modifiers,
                         size_t modifiersCount, const CombinationKeys &keys,
                         size_t keysCount)
    : Combination(modifiers, modifiersCount) {
    if (keysCount > m_keys.size()) {
        // TODO
    }

    for (int i{0}; i != keysCount; ++i) {
        m_keys[i] = keys[i];
        ++m_keysCount;
    }
}

[[nodiscard]] auto Combination::getModifiersSlotsLeft() const -> size_t {
    return m_modifiers.size() - m_modifiersCount;
}

[[nodiscard]] auto Combination::getKeysSlotsLeft() const -> size_t {
    return m_keys.size() - m_keysCount;
}

[[nodiscard]] auto Combination::getModifiers() const -> CombinationModifiers {
    return m_modifiers;
}

[[nodiscard]] auto Combination::getKeys() const -> CombinationKeys {
    return m_keys;
}

[[nodiscard]] auto Combination::getModifiersCount() const -> size_t {
    return m_modifiersCount;
}

[[nodiscard]] auto Combination::getKeysCount() const -> size_t {
    return m_keysCount;
}

[[nodiscard]] auto Combination::isEmpty() const -> bool {
    return m_modifiersCount == 0 && m_keysCount == 0;
}

[[nodiscard]] auto Combination::isNoModifiers() const -> bool {
    return !isEmpty() && m_modifiersCount == 0;
}

auto Combination::addModifier(const Keys::Modifiers modifier) -> void {
    if (0 == getModifiersSlotsLeft()) {
        // TODO
        return;
    }

    m_modifiers[m_modifiersCount] = modifier;
    ++m_modifiersCount;
}

auto Combination::addKey(const Keys::Printables key) -> void {
    if (0 == getKeysSlotsLeft()) {
        // TODO
        return;
    }

    m_keys[m_keysCount] = key;
    ++m_keysCount;
}
