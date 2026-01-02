#ifndef APP_TYPES_HPP
#define APP_TYPES_HPP

#include <combination.hpp>
#include <keys.hpp>

namespace app::types {
constexpr size_t maxCombinationsInMapping{5};

using Combinations = std::array<comb::Combination, maxCombinationsInMapping>;

class KeyCombinationBinding {
  private:
    std::array<Combinations, key::keysCount> m_array;

  public:
    constexpr KeyCombinationBinding(const comb::Combination &combination)
        : m_array{combination} {}

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
    KeyCombinationBinding keyCombinationBinding{comb::Combination()};

    using key::Keys, comb::Combination;

    keyCombinationBinding[Keys::J] = {
        Combination({.array = {Keys::RIGHT_CMD, Keys::RIGHT_ALT,
                               Keys::LEFT_CTRL, Keys::LEFT_SHIFT},
                     .count = 4})};

    keyCombinationBinding[Keys::K] = {
        Combination({.array = {Keys::RIGHT_CMD}, .count = 1})};

    keyCombinationBinding[Keys::A] = {
        Combination({.array = {Keys::S}, .count = 1})};

    keyCombinationBinding[Keys::S] = {
        Combination({.array = {Keys::H, Keys::I}, .count = 2})};

    return keyCombinationBinding;
};

const KeyCombinationBinding keyCombinationBinding{
    createKeyCombinationBinding()};
} // namespace app::types

#endif // APP_TYPES_HPP
