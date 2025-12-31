#ifndef APP_TYPES_HPP
#define APP_TYPES_HPP

#include <combination.hpp>
#include <keys.hpp>

namespace app::types {

class KeyCombinationBinding {
  private:
    std::array<comb::Combination, key::keysCount> m_array;

  public:
    constexpr KeyCombinationBinding(const comb::Combination &combination)
        : m_array{combination} {}

    [[nodiscard]] auto at(key::Keys key) const -> comb::Combination {
        // TODO bound check
        return m_array.at(static_cast<size_t>(key));
    }

    constexpr auto operator[](key::Keys key) -> comb::Combination & {
        // TODO bound check
        return m_array.at(static_cast<size_t>(key));
    }
};

inline auto createKeyCombinationBinding() -> KeyCombinationBinding {
    KeyCombinationBinding keyCombinationBinding{comb::Combination()};

    using key::Keys, comb::Combination;

    keyCombinationBinding[Keys::J] = Combination(
        {Keys::RIGHT_CMD, Keys::RIGHT_ALT, Keys::LEFT_CTRL, Keys::LEFT_SHIFT},
        4);

    keyCombinationBinding[Keys::K] = Combination({Keys::RIGHT_CMD}, 1);

    keyCombinationBinding[Keys::A] = Combination({Keys::S}, 1);

    return keyCombinationBinding;
};

const KeyCombinationBinding keyCombinationBinding{
    createKeyCombinationBinding()};
} // namespace app::types

#endif // APP_TYPES_HPP
