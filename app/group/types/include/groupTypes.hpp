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
class Subgroups {
  private:
    std::array<std::unique_ptr<Group>, key::keysCount> m_array;
    size_t m_count;

  public:
    Subgroups();

    auto add(std::unique_ptr<Group> group) -> void;

    auto at(key::Keys key) -> const Group *;
};

constexpr size_t maxCombinationsInMapping{5};

struct Combinations {
    std::array<comb::Combination, maxCombinationsInMapping> array;
    size_t count = 1;
};

class Bindings {
  private:
    std::array<Combinations, key::keysCount> m_array;

  public:
    Bindings() : m_array{} {}
    Bindings(const Combinations &combinations) : m_array{combinations} {}

    [[nodiscard]] auto at(key::Keys key) const -> Combinations {
        // TODO bound check
        return m_array.at(static_cast<size_t>(key));
    }

    auto operator[](key::Keys key) -> Combinations & {
        // TODO bound check
        return m_array.at(static_cast<size_t>(key));
    }
};

} // namespace grp::types

#endif // GROUP_TYPES_HPP
