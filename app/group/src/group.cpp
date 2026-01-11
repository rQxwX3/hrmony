#include <group.hpp>

grp::Group::Group(const key::Keys leader, const grp::types::Bindings &bindings)
    : m_leader{leader}, m_bindings{bindings},
      m_subgroups(std::make_unique<grp::types::Subgroups>()) {}

[[nodiscard]] auto grp::Group::getLeader() const -> key::Keys {
    return m_leader;
}

[[nodiscard]] auto
grp::Group::getBindings() const & -> const grp::types::Bindings & {
    return m_bindings;
}

[[nodiscard]] auto grp::Group::getSubgroup(key::Keys leader) const
    -> const Group * {
    return m_subgroups->at(leader);
}

auto grp::Group::addSubgroup(std::unique_ptr<Group> groupPtr) -> void {
    m_subgroups->set(std::move(groupPtr));
}
