#include "types.hpp"

namespace AppDefaults {

constexpr auto createKeyBindingArray() -> KeyBindingArray {
    KeyBindingArray arr{};

    arr[static_cast<size_t>(Key::A)] = Key::S;

    return arr;
};

constexpr KeyBindingArray keyBindingArray{createKeyBindingArray()};
} // namespace AppDefaults
