#include <action.hpp>
#include <group.hpp>
#include <optional>

namespace grp::types {

Action::Action()
    : m_variant{std::unique_ptr<Group>{}}, m_type{Action::Type::NULLACTION} {}

Action::Action(Variant variant)
    : m_variant{std::move(variant)}, m_type{Action::Type::NULLACTION} {
    if (std::holds_alternative<Combinations>(m_variant)) {
        m_type = Action::Type::BINDING;
    } else if (std::holds_alternative<std::unique_ptr<Group>>(m_variant)) {
        m_type = Action::Type::SUBGROUP;
    }
}

[[nodiscard]] auto Action::getSubgroup() const -> std::optional<const Group *> {
    const auto *subgroup{std::get_if<std::unique_ptr<Group>>(&m_variant)};

    if (subgroup == nullptr) {
        return {};
    }

    return subgroup->get();
}

[[nodiscard]] auto Action::getBinding() const
    -> std::optional<const Combinations> {
    const auto *binding{std::get_if<grp::types::Combinations>(&m_variant)};

    if (nullptr == binding) {
        return {};
    }

    return *binding;
}

[[nodiscard]] auto Action::getType() const -> Action::Type { return m_type; }

[[nodiscard]] auto Actions::at(key::Keys key) const & -> const Action & {
    const auto index{static_cast<size_t>(key)};

    if (index > m_array.size()) {
        // TODO
    }

    return m_array[index];
}

[[nodiscard]] auto Actions::at(key::Keys key) & -> grp::types::Action & {
    const auto index{static_cast<size_t>(key)};

    if (index > m_array.size()) {
        // TODO
    }

    return m_array[index];
}
} // namespace grp::types
