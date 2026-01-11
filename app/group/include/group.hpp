#ifndef GROUP_HPP
#define GROUP_HPP

#include <groupTypes.hpp>
#include <keys.hpp>

namespace grp {
class Group {
  private:
    // grp::types::Subgroups m_subgroups;
    grp::types::Bindings m_bindings;
    key::Keys m_leader;

  public:
    Group();

    Group(key::Keys leader, const grp::types::Bindings &bindings);

  public:
    [[nodiscard]] auto getLeader() const -> key::Keys;
    [[nodiscard]] auto getBindings() const & -> const grp::types::Bindings &;

  public:
    [[nodiscard]] auto isNullGroup() const -> bool;
};

inline auto createGlobalGroup() -> grp::Group {
    grp::types::Bindings bindings{{.array = {comb::Combination()}, .count = 1}};

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

    return Group{key::Keys::RIGHT_CMD, bindings};
};

const grp::Group nullGroup{};
} // namespace grp

#endif // GROUP_HPP
