#ifndef COMBINATION_HPP
#define COMBINATION_HPP

#include <types.hpp>

namespace comb {
class Combination {
  private:
    CombinationModifiers m_modifiers;
    CombinationRegulars m_regulars;

    size_t m_regularsCount;
    size_t m_modifiersCount;

  public:
    Combination();

    Combination(const CombinationRegulars &keys, size_t keysCount);

  public:
    [[nodiscard]] auto getModifiersSlotsLeft() const -> size_t;
    [[nodiscard]] auto getRegularsSlotsLeft() const -> size_t;

  public:
    [[nodiscard]] auto getModifiers() const -> CombinationModifiers;
    [[nodiscard]] auto getRegulars() const -> CombinationRegulars;

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
