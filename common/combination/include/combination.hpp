#ifndef COMBINATION_HPP
#define COMBINATION_HPP

#include <types.hpp>

class Combination {
  private:
    CombinationModifiers m_modifiers{Keys::Modifiers::NULLKEY};
    CombinationKeys m_keys{Keys::Printables::NULLKEY};

    size_t m_modifiersCount{0};
    size_t m_keysCount{0};

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

  public:
    auto addModifier(Keys::Modifiers modifier) -> void;
    auto addKey(Keys::Printables key) -> void;
};

#endif // COMBINATION_HPP
