#include <combination.hpp>

comb::Combination::Combination()
    : m_regulars{}, m_regularsCount{0}, m_modifiersCount{0} {}

comb::Combination::Combination(const CombinationRegulars &keys,
                               size_t keysCount)
    : Combination() {

    for (int i{0}; i != keysCount; ++i) {
        const auto key = keys.at(i);

        addKey(key);
    }
}

[[nodiscard]] auto comb::Combination::getRegularsSlotsLeft() const -> size_t {
    return m_regulars.size() - m_regularsCount;
}

[[nodiscard]] auto comb::Combination::getModifiersSlotsLeft() const -> size_t {
    return m_modifiers.size() - m_modifiersCount;
}

[[nodiscard]] auto comb::Combination::getRegulars() const
    -> CombinationRegulars {
    return m_regulars;
}

[[nodiscard]] auto comb::Combination::getModifiers() const
    -> CombinationModifiers {
    return m_modifiers;
}

[[nodiscard]] auto comb::Combination::getRegularsCount() const -> size_t {
    return m_regularsCount;
}

[[nodiscard]] auto comb::Combination::getModifiersCount() const -> size_t {
    return m_modifiersCount;
}

[[nodiscard]] auto comb::Combination::isEmpty() const -> bool {
    return m_regularsCount == 0;
}

[[nodiscard]] auto comb::Combination::isNoModifiers() const -> bool {
    return !isEmpty() && m_modifiersCount == 0;
}

auto comb::Combination::addModifier(const key::Keys key) -> void {
    if (0 == getModifiersSlotsLeft()) {
        // TODO
        return;
    }

    m_modifiers[m_modifiersCount] = key;
    ++m_modifiersCount;
}

auto comb::Combination::addRegular(const key::Keys key) -> void {
    if (0 == getRegularsSlotsLeft()) {
        // TODO
        return;
    }

    m_regulars[m_regularsCount] = key;
    ++m_regularsCount;
}

auto comb::Combination::addKey(const key::Keys key) -> void {
    if (key::isModifier(key)) {
        addModifier(key);
    } else {
        addRegular(key);
    }
}
