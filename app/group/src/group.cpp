#include <group.hpp>
#include <groupTypes.hpp>

grp::Group::Group(const key::Keys leader) : m_leader{leader}, m_actions{} {}

[[nodiscard]] auto grp::Group::getLeader() const -> key::Keys {
    return m_leader;
}

[[nodiscard]] auto grp::Group::getAction(key::Keys key) const
    -> grp::types::Action * {
    return m_actions.at(static_cast<size_t>(key)).get();
}

auto grp::Group::addAction(key::Keys key,
                           const grp::types::Combinations &combinations)
    -> void {
    m_actions.at(static_cast<size_t>(key)) =
        std::make_unique<grp::types::Binding>(combinations);
}

auto grp::Group::addAction(std::unique_ptr<grp::Group> group) -> void {
    const auto actionsIndex{static_cast<size_t>(group->getLeader())};

    m_actions.at(actionsIndex) =
        std::make_unique<grp::types::Subgroup>(std::move(group));
}
