#ifndef COMBINATION_TYPES_HPP
#define COMBINATION_TYPES_HPP

#include <keys.hpp>

#include <array>

namespace comb::types {
constexpr size_t maxKeymapModifiers{4};
constexpr size_t maxKeymapRegulars{4};
constexpr size_t maxKeymapKeys{maxKeymapModifiers + maxKeymapRegulars};

using Modifiers = std::array<key::Keys, maxKeymapModifiers>;
using Regulars = std::array<key::Keys, maxKeymapRegulars>;

class Keys {
    using Array = std::array<key::Keys, maxKeymapKeys>;

  private:
    Array m_array;

  public:
    constexpr Keys() : m_array{key::Keys::NULLKEY} {}

    constexpr Keys(Array keys, size_t keysCount) : Keys() {
        // TODO bound check
        for (int i{0}; i != keysCount; ++i) {
            m_array.at(i) = keys.at(i);
        }
    }

    constexpr auto at(size_t i) -> key::Keys & { return m_array.at(i); }

    constexpr auto at(size_t i) const -> const key::Keys & {
        return m_array.at(i);
    }
};
} // namespace comb::types

#endif // COMBINATION_TYPES_HPP
