#ifndef COMBINATION_HPP
#define COMBINATION_HPP

#include <combinationTypes.hpp>

namespace comb {
class Combination {
  private:
    comb::types::Modifiers m_modifiers;
    comb::types::Regulars m_regulars;

    size_t m_regularsCount;
    size_t m_modifiersCount;

  public:
    Combination();

    Combination(const comb::types::Keys &keys, size_t keysCount);

  public:
    [[nodiscard]] auto getModifiersSlotsLeft() const -> size_t;
    [[nodiscard]] auto getRegularsSlotsLeft() const -> size_t;

  public:
    [[nodiscard]] auto getModifiers() const -> comb::types::Modifiers;

    [[nodiscard]] auto getRegulars() const -> comb::types::Regulars;

    [[nodiscard]] auto getModifiersCount() const -> size_t;
    [[nodiscard]] auto getRegularsCount() const -> size_t;

  public:
    [[nodiscard]] auto isEmpty() const -> bool;
    [[nodiscard]] auto isNoModifiers() const -> bool;

  public:
    auto addKey(key::Keys key) -> void;

    auto addModifier(key::Keys key) -> void;
    auto addRegular(key::Keys key) -> void;
};
} // namespace comb

#endif // COMBINATION_HPP
