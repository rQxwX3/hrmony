#ifndef GROUP_TYPES_HPP
#define GROUP_TYPES_HPP

#include <combination.hpp>
#include <keys.hpp>

#include <array>
#include <memory>

namespace grp {
class Group;
}

namespace grp::types {
struct Action {
    enum class Type : uint8_t { Subgroup, Binding };

    [[nodiscard]] virtual auto getType() const -> const Type = 0;

    virtual ~Action() = default;
};

using Actions = std::array<std::unique_ptr<Action>, key::keysCount>;

class Subgroup : public Action {
  private:
    std::unique_ptr<grp::Group> m_group;

  public:
    Subgroup(std::unique_ptr<grp::Group> group);
    ~Subgroup() override;

  public:
    [[nodiscard]] auto getType() const -> const Type override;

  public:
    [[nodiscard]] auto getGroup() const -> const grp::Group *;
    [[nodiscard]] auto getLeader() const -> key::Keys;
};

struct Combinations {
    static constexpr size_t maxCombinationsInMapping{5};

    std::array<comb::Combination, maxCombinationsInMapping> combinations;
    size_t count = 1;
};

class Binding : public Action {
  private:
    Combinations m_combinations;

  public:
    Binding(const Combinations &combinations);
    ~Binding() override;

  public:
    [[nodiscard]] auto getType() const -> const Type override;

  public:
    [[nodiscard]] auto getBinding() const -> Combinations;
};
} // namespace grp::types

#endif // GROUP_TYPES_HPP
