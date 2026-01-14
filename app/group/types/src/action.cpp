#include <action.hpp>
#include <group.hpp>
#include <optional>

grp::types::Action::Action() : variant{std::unique_ptr<Group>{}} {}

grp::types::Action::Action(Variant variant) : variant{std::move(variant)} {}

[[nodiscard]] auto grp::types::Action::getSubgroup() const
    -> std::optional<const Group *> {
    const auto *subgroup{std::get_if<std::unique_ptr<Group>>(&variant)};

    if (subgroup == nullptr) {
        return {};
    }

    return subgroup->get();
}

[[nodiscard]] auto grp::types::Action::getBinding() const
    -> std::optional<const Combinations> {
    const auto *binding{std::get_if<grp::types::Combinations>(&variant)};

    if (nullptr == binding) {
        return {};
    }

    return *binding;
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

[[nodiscard]] auto
grp::types::Actions::at(key::Keys key) const & -> const Action & {
    const auto index{static_cast<size_t>(key)};

    if (index > m_array.size()) {
        // TODO
    }

    return m_array[index];
}

[[nodiscard]] auto
grp::types::Actions::at(key::Keys key) & -> grp::types::Action & {
    const auto index{static_cast<size_t>(key)};

    if (index > m_array.size()) {
        // TODO
    }

    return m_array[index];
}
