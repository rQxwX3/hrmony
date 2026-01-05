#ifndef APP_TYPES_HPP
#define APP_TYPES_HPP

#include <group.hpp>
#include <keys.hpp>

namespace app::types {

struct Groups {
    std::array<grp::Group, key::keysCount> array;
    size_t count{0};
};

inline auto createGroups() -> Groups {
    return {.array = {grp::createGlobalGroup()}, .count = 1};
}
} // namespace app::types

#endif // APP_TYPES_HPP
