#include <group.hpp>

grp::Group::Group() : m_leader{key::Keys::NULLKEY} {}

grp::Group::Group(const key::Keys leader, const grp::types::Bindings &bindings)
    : m_leader{leader}, m_bindings{bindings} {}

[[nodiscard]] auto grp::Group::getLeader() const -> key::Keys {
    return m_leader;
}

[[nodiscard]] auto grp::Group::getBindings() const
    -> const grp::types::Bindings & {
    return m_bindings;
}

[[nodiscard]] auto grp::Group::getSubgroups() const
    -> const grp::types::Subgroups & {
    return m_subgroups;
}

auto grp::Group::addSubgroup(std::unique_ptr<Group> group) -> void {
    // TODO bound check
}

[[nodiscard]] auto grp::Group::isNullGroup() const -> bool {
    return m_leader == key::Keys::NULLKEY;
}
