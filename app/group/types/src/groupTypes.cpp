#include <group.hpp>

#include <groupTypes.hpp>

#include <memory>

grp::types::Subgroups::Subgroups() : m_array{nullptr}, m_count{0} {}

auto grp::types::Subgroups::add(std::unique_ptr<Group> group) -> void {
    m_array.at(m_count) = std::move(group);
    ++m_count;
}

auto grp::types::Subgroups::at(key::Keys key) -> const Group * {
    // TODO bound check
    return m_array.at(static_cast<size_t>(key)).get();
}
