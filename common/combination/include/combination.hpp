#ifndef COMBINATION_HPP
#define COMBINATION_HPP

#include <combinationTypes.hpp>

namespace comb {
class Combination {
  private:
    comb::types::Modifiers m_modifiers;
    comb::types::Regulars m_regulars;

  public:
    Combination();

    Combination(const comb::types::Modifiers &modifiers,
                const comb::types::Regulars &regulars);

    Combination(const comb::types::Keys &keys);

  public:
    [[nodiscard]] auto getModifiersSlotsLeft() const -> size_t;
    [[nodiscard]] auto getRegularsSlotsLeft() const -> size_t;

  public:
    [[nodiscard]] auto getModifiers() const -> comb::types::Modifiers;
    [[nodiscard]] auto getRegulars() const -> comb::types::Regulars;
    [[nodiscard]] auto getKeys() const -> comb::types::Keys;

  public:
    [[nodiscard]] auto isEmpty() const -> bool;
    [[nodiscard]] auto isSendable() const -> bool;

    [[nodiscard]] auto containsNoModifiers() const -> bool;
    [[nodiscard]] auto containsNoRegulars() const -> bool;
    [[nodiscard]] auto containsMultipleRegulars() const -> bool;

  public:
    auto addKey(key::Keys key) -> void;

    auto addModifier(key::Keys key) -> void;
    auto addRegular(key::Keys key) -> void;
};
} // namespace comb

#endif // COMBINATION_HPP
