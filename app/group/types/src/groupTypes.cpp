#include <group.hpp>
#include <groupTypes.hpp>

auto grp::types::Subgroups::addSubgroup(key::Keys leader,
                                        std::unique_ptr<grp::Group> group)
    -> void {
    // TODO bound check
    // TODO check if leader was occupied
    // TODO incapsulate static_cast
    m_array.at(static_cast<size_t>(leader)) = std::move(group);
}
