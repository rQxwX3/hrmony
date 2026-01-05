#ifndef GROUP_HPP
#define GROUP_HPP

#include <groupTypes.hpp>
#include <keys.hpp>

namespace grp {
class Group {
  private:
    key::Keys m_leader;
    grp::types::Bindings m_bindings;

  public:
    Group(key::Keys leader, const grp::types::Bindings &bindings);

  public:
    [[nodiscard]] auto getLeader() const -> key::Keys;
    [[nodiscard]] auto getBindings() const -> grp::types::Bindings;
};
} // namespace grp

#endif // GROUP_HPP
