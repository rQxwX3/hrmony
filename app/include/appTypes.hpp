#ifndef APP_TYPES_HPP
#define APP_TYPES_HPP

#include <combination.hpp>
#include <keys.hpp>

namespace app::types {

using KeyBindingArray = std::array<comb::Combination, key::keysCount>;

inline auto createKeyBindingArray() -> KeyBindingArray {
    KeyBindingArray arr{comb::Combination()};

    using key::Keys;

    arr[static_cast<size_t>(Keys::J)] = comb::Combination(
        {Keys::RIGHT_CMD, Keys::RIGHT_ALT, Keys::LEFT_CTRL, Keys::LEFT_SHIFT},
        4);

    arr[static_cast<size_t>(Keys::K)] = comb::Combination({Keys::RIGHT_CMD}, 1);

    arr[static_cast<size_t>(Keys::A)] = comb::Combination({Keys::S}, 1);

    return arr;
};

const KeyBindingArray keyBindingArray{createKeyBindingArray()};
} // namespace app::types

#endif // APP_TYPES_HPP
