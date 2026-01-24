#ifndef ACTION_HPP
#define ACTION_HPP

#include <combination.hpp>
#include <keys.hpp>

#include <array>
#include <memory>
#include <optional>
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

class Action {
  public:
    using Variant = std::variant<Combinations, std::unique_ptr<Group>>;
    using Type = enum class Type : uint8_t { EMPTY, BINDING, SUBGROUP };

  private:
    Variant m_variant;
    Type m_type;

  public:
    Action();
    Action(Variant variant);

  public:
    [[nodiscard]] auto getSubgroup() const -> std::optional<const Group *>;
    [[nodiscard]] auto getBinding() const -> std::optional<const Combinations>;
    [[nodiscard]] auto getType() const -> Action::Type;
};

class Actions {
  private:
    std::array<grp::types::Action, key::keysCount> m_array;

  public:
    [[nodiscard]] auto at(key::Keys key) const & -> const grp::types::Action &;
    [[nodiscard]] auto at(key::Keys key) & -> grp::types::Action &;
};
} // namespace grp::types

#endif // ACTION_HPP
