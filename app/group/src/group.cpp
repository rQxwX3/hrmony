#include <group.hpp>

namespace grp {

Group::Group(const key::Keys leader, bool isGlobalSubgroup)
    : m_leader{leader}, m_actions{std::make_unique<grp::types::Actions>()},
      m_isGlobalSubgroup{true} {}

[[nodiscard]] auto Group::isGlobalSubgroup() const -> bool {
    return m_isGlobalSubgroup;
}

[[nodiscard]] auto Group::getLeader() const -> key::Keys { return m_leader; }

[[nodiscard]] auto
Group::getAction(key::Keys key) const & -> const grp::types::Action & {
    return m_actions->at(key);
}

auto Group::addAction(key::Keys key,
                      const grp::types::Combinations &combinations) -> void {
    m_actions->at(key) = grp::types::Action(combinations);
}

auto Group::addAction(std::unique_ptr<grp::Group> group) -> void {
    const auto leader{group->getLeader()};

    m_actions->at(leader) = grp::types::Action(std::move(group));
}
} // namespace grp
