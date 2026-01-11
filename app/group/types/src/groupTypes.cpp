#include <group.hpp>
#include <groupTypes.hpp>

#include <iostream>

auto grp::types::Subgroups::set(std::unique_ptr<Group> group) -> void {
    m_array.at(static_cast<size_t>(group->getLeader())) = std::move(group);
}

[[nodiscard]] auto grp::types::Subgroups::at(key::Keys leader) const
    -> const grp::Group * {
    return m_array.at(static_cast<size_t>(leader)).get();
}
