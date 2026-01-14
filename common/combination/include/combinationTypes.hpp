#ifndef COMBINATION_TYPES_HPP
#define COMBINATION_TYPES_HPP

#include <keys.hpp>

#include <array>

namespace comb::types {
constexpr size_t maxKeymapModifiers{4};
constexpr size_t maxKeymapRegulars{4};
constexpr size_t maxKeymapKeys{maxKeymapModifiers + maxKeymapRegulars};

struct Modifiers {
    std::array<key::Keys, maxKeymapModifiers> array;
    size_t count;
};

struct Regulars {
    std::array<key::Keys, maxKeymapRegulars> array;
    size_t count;
};

struct Keys {
    std::array<key::Keys, maxKeymapKeys> array;
    size_t count;
};
} // namespace comb::types

#endif // COMBINATION_TYPES_HPP
