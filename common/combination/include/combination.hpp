#ifndef COMBINATION_HPP
#define COMBINATION_HPP

#include <types.hpp>

class Combination {
  private:
    CombinationModifiers m_modifiers;
    CombinationKeys m_keys;

    size_t m_modifiersCount;
    size_t m_keysCount;

  public:
    Combination();

    Combination(const CombinationModifiers &modifiers, size_t modifiersCount);

    Combination(const CombinationKeys &keys, size_t keysCount);

    Combination(const CombinationModifiers &modifiers, size_t modifiersCount,
                const CombinationKeys &keys, size_t keysCount);

  public:
    [[nodiscard]] auto getModifiersSlotsLeft() const -> size_t;
    [[nodiscard]] auto getKeysSlotsLeft() const -> size_t;

  public:
    [[nodiscard]] auto getModifiers() const -> CombinationModifiers;
    [[nodiscard]] auto getKeys() const -> CombinationKeys;

  public:
    [[nodiscard]] auto isEmpty() const -> bool;
    [[nodiscard]] auto isNoModifiers() const -> bool;

  public:
    auto addModifier(Keys::Modifiers modifier) -> void;
    auto addKey(Keys::Printables key) -> void;
};

#endif // COMBINATION_HPP
