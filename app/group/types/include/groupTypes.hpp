#ifndef GROUP_TYPES_HPP
#define GROUP_TYPES_HPP

#include <combination.hpp>
#include <keys.hpp>

#include <array>
#include <memory>
#include <variant>

namespace grp {
class Group;
}

namespace grp::types {
struct Combinations {
    static constexpr size_t maxCombinationsInMapping{5};

    std::array<comb::Combination, maxCombinationsInMapping> combinations;
    size_t count = 1;
};

struct Action {
    using Variant = std::variant<Combinations, std::unique_ptr<Group>>;

    Variant variant;

    Action();
    Action(Variant variant);

    [[nodiscard]] auto isBinding() const -> bool;
    [[nodiscard]] auto isSubgroup() const -> bool;
    [[nodiscard]] auto isEmpty() const -> bool;

    [[nodiscard]] auto getSubgroup() const -> const Group *;
    [[nodiscard]] auto getBinding() const & -> const Combinations &;
};

using Actions = std::array<Action, key::keysCount>;
} // namespace grp::types

#endif // GROUP_TYPES_HPP
