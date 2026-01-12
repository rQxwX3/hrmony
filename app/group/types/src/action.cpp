#include <action.hpp>
#include <group.hpp>

grp::types::Action::Action() : variant{std::unique_ptr<Group>{}} {}

grp::types::Action::Action(Variant variant) : variant{std::move(variant)} {}

[[nodiscard]] auto grp::types::Action::getSubgroup() const -> const Group * {
    return std::get<std::unique_ptr<Group>>(variant).get();
}

[[nodiscard]] auto
grp::types::Action::getBinding() const & -> const Combinations & {
    return std::get<grp::types::Combinations>(variant);
}

[[nodiscard]] auto grp::types::Action::isBinding() const -> bool {
    return std::holds_alternative<Combinations>(variant);
}

[[nodiscard]] auto grp::types::Action::isSubgroup() const -> bool {
    return std::holds_alternative<std::unique_ptr<Group>>(variant) &&
           getSubgroup() != nullptr;
}

[[nodiscard]] auto grp::types::Action::isEmpty() const -> bool {
    return !isBinding() && getSubgroup() == nullptr;
}
