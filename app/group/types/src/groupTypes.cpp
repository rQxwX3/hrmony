#include <group.hpp>
#include <groupTypes.hpp>

grp::types::Binding::Binding(const Combinations &combinations)
    : m_combinations{combinations} {}

grp::types::Binding::~Binding() = default;

[[nodiscard]] auto grp::types::Binding::getType() const -> const Type {
    return Type::Binding;
}

grp::types::Subgroup::Subgroup(std::unique_ptr<grp::Group> group)
    : m_group{std::move(group)} {}

grp::types::Subgroup::~Subgroup() = default;

[[nodiscard]] auto grp::types::Binding::getBinding() const -> Combinations {
    return m_combinations;
}

[[nodiscard]] auto grp::types::Subgroup::getType() const -> const Type {
    return Type::Subgroup;
}

[[nodiscard]] auto grp::types::Subgroup::getGroup() const
    -> const grp::Group * {
    return m_group.get();
}

[[nodiscard]] auto grp::types::Subgroup::getLeader() const -> key::Keys {
    return m_group->getLeader();
}
