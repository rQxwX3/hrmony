#ifndef COMBINATION_TYPES_HPP
#define COMBINATION_TYPES_HPP

#include <keys.hpp>

#include <array>

namespace comb::types {
constexpr size_t maxKeymapModifiers{4};
constexpr size_t maxKeymapRegulars{4};
constexpr size_t maxKeymapKeys{maxKeymapModifiers + maxKeymapRegulars};

using Keys = std::array<key::Keys, maxKeymapKeys>;
using Modifiers = std::array<key::Keys, maxKeymapModifiers>;
using Regulars = std::array<key::Keys, maxKeymapRegulars>;
} // namespace comb::types

#endif // COMBINATION_TYPES_HPP
