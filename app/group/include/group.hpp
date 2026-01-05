#ifndef GROUP_HPP
#define GROUP_HPP

#include <groupTypes.hpp>
#include <keys.hpp>

namespace grp {
class Group {
  private:
    key::Keys m_leader{key::Keys::NULLKEY};
    grp::types::Bindings m_bindings;
};
} // namespace grp

#endif // GROUP_HPP
