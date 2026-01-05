#ifndef GROUP_TYPES_HPP
#define GROUP_TYPES_HPP

#include <combination.hpp>
#include <keys.hpp>

#include <array>

namespace grp::types {
constexpr size_t maxCombinationsInMapping{5};

struct Combinations {
    std::array<comb::Combination, maxCombinationsInMapping> array;
    size_t count = 1;
};

class Bindings {
  private:
    std::array<Combinations, key::keysCount> m_array;

  public:
    Bindings(const Combinations &combinations) : m_array{combinations} {}

    [[nodiscard]] auto at(key::Keys key) const -> Combinations {
        // TODO bound check
        return m_array.at(static_cast<size_t>(key));
    }

    auto operator[](key::Keys key) -> Combinations & {
        // TODO bound check
        return m_array.at(static_cast<size_t>(key));
    }
};

inline auto createBindings() -> Bindings {
    Bindings bindings{{.array = {comb::Combination()}, .count = 1}};

    using key::Keys, comb::Combination;

    bindings[Keys::J] = {
        .array = {Combination({.array = {Keys::RIGHT_CMD, Keys::RIGHT_ALT,
                                         Keys::LEFT_CTRL, Keys::LEFT_SHIFT},
                               .count = 4})},
        .count = 1};

    bindings[Keys::K] = {
        .array =
            {Combination({.array = {Keys::RIGHT_CMD, Keys::T}, .count = 2}),
             Combination({.array = {Keys::RIGHT_CMD, Keys::W}, .count = 2})},
        .count = 2};

    bindings[Keys::A] = {.array = {Combination(
                             {.array = {Keys::S}, .count = 1})},
                         .count = 1},

    bindings[Keys::S] = {
        .array = {Combination({.array = {Keys::H, Keys::I}, .count = 2})},
        .count = 1};

    return bindings;
};

const Bindings keyCombinationBinding{createBindings()};
} // namespace grp::types

#endif // GROUP_TYPES_HPP
