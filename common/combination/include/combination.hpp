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
    constexpr Combination() = default;

    constexpr Combination(const CombinationModifiers &modifiers,
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

    constexpr Combination(const CombinationKeys &keys, size_t keysCount);

    constexpr Combination(const CombinationModifiers &modifiers,
                          size_t modifiersCount, const CombinationKeys &keys,
                          size_t keysCount);

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
