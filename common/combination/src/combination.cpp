#include <combination.hpp>
#include <keys.hpp>

comb::Combination::Combination()
    : m_regulars{.array = {key::Keys::NULLKEY}, .count = 0},
      m_modifiers{.array = {key::Keys::NULLKEY}, .count = 0} {}

comb::Combination::Combination(const comb::types::Keys &keys) : Combination() {
    for (size_t i{0}; i != keys.count; ++i) {
        const auto key = keys.array.at(i);

        addKey(key);
    }
}

comb::Combination::Combination(const comb::types::Modifiers &modifiers,
                               const comb::types::Regulars &regulars)
    : Combination() {
    for (size_t i{0}; i != modifiers.count; ++i) {
        addKey(modifiers.array.at(i));
    }

    for (size_t i{0}; i != regulars.count; ++i) {
        addKey(regulars.array.at(i));
    }
}

[[nodiscard]] auto comb::Combination::getRegularsSlotsLeft() const -> size_t {
    return m_regulars.array.size() - m_regulars.count;
}

[[nodiscard]] auto comb::Combination::getModifiersSlotsLeft() const -> size_t {
    return m_modifiers.array.size() - m_modifiers.count;
}

[[nodiscard]] auto comb::Combination::getRegulars() const
    -> comb::types::Regulars {
    return m_regulars;
}

[[nodiscard]] auto comb::Combination::getModifiers() const
    -> comb::types::Modifiers {
    return m_modifiers;
}

[[nodiscard]] auto comb::Combination::getKeys() const -> comb::types::Keys {
    comb::types::Keys keys{.array = {key::Keys::NULLKEY}, .count = 0};

    for (const auto &mod : m_modifiers.array) {
        keys.array.at(keys.count++) = mod;
    }

    for (const auto &reg : m_regulars.array) {
        keys.array.at(keys.count++) = reg;
    }

    return keys;
}

[[nodiscard]] auto comb::Combination::isEmpty() const -> bool {
    return m_regulars.count == 0 && m_modifiers.count == 0;
}

[[nodiscard]] auto comb::Combination::isSendable() const -> bool {
    return m_regulars.count == 1;
}

[[nodiscard]] auto comb::Combination::containsNoModifiers() const -> bool {
    return !isEmpty() && m_modifiers.count == 0;
}

[[nodiscard]] auto comb::Combination::containsNoRegulars() const -> bool {
    return !isEmpty() && m_regulars.count == 0;
}

[[nodiscard]] auto comb::Combination::containsMultipleRegulars() const -> bool {
    return m_regulars.count > 1;
}

auto comb::Combination::addModifier(const key::Keys key) -> void {
    if (0 == getModifiersSlotsLeft()) {
        // TODO
        return;
    }

    m_modifiers.array[m_modifiers.count] = key;
    ++m_modifiers.count;
}

auto comb::Combination::addRegular(const key::Keys key) -> void {
    if (0 == getRegularsSlotsLeft()) {
        // TODO
        return;
    }

    m_regulars.array[m_regulars.count] = key;
    ++m_regulars.count;
}

auto comb::Combination::addKey(const key::Keys key) -> void {
    if (key::isModifier(key)) {
        addModifier(key);
    } else {
        addRegular(key);
    }
}
