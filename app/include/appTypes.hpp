#ifndef APP_TYPES_HPP
#define APP_TYPES_HPP

#include <combination.hpp>
#include <keys.hpp>

namespace app::types {

constexpr size_t maxCombinationsInMapping{5};

struct Combinations {
    std::array<comb::Combination, maxCombinationsInMapping> array;
    size_t count = 1;
};

class KeyCombinationBinding {
  private:
    std::array<Combinations, key::keysCount> m_array;

  public:
    constexpr KeyCombinationBinding(const Combinations &combinations)
        : m_array{combinations} {}

    [[nodiscard]] auto at(key::Keys key) const -> Combinations {
        // TODO bound check
        return m_array.at(static_cast<size_t>(key));
    }

    constexpr auto operator[](key::Keys key) -> Combinations & {
        // TODO bound check
        return m_array.at(static_cast<size_t>(key));
    }
};

inline auto createKeyCombinationBinding() -> KeyCombinationBinding {
    KeyCombinationBinding keyCombinationBinding{
        {.array = {comb::Combination()}, .count = 1}};

    using key::Keys, comb::Combination;

    keyCombinationBinding[Keys::J] = {
        .array = {Combination({.array = {Keys::RIGHT_CMD, Keys::RIGHT_ALT,
                                         Keys::LEFT_CTRL, Keys::LEFT_SHIFT},
                               .count = 4})},
        .count = 1};

    keyCombinationBinding[Keys::K] = {
        .array = {Combination({.array = {Keys::RIGHT_CMD}, .count = 1})},
        .count = 1};

    keyCombinationBinding[Keys::A] = {.array = {Combination(
                                          {.array = {Keys::S}, .count = 1})},
                                      .count = 1},

    keyCombinationBinding[Keys::S] = {
        .array = {Combination({.array = {Keys::H, Keys::I}, .count = 2})},
        .count = 1};

    return keyCombinationBinding;
};

const KeyCombinationBinding keyCombinationBinding{
    createKeyCombinationBinding()};
} // namespace app::types

#endif // APP_TYPES_HPP
