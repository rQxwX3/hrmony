#include "types.hpp"

namespace AppDefaults {

constexpr auto createKeyBindingArray() -> KeyBindingArray {
    KeyBindingArray arr{Keys::Modifiers::NULLKEY};

    arr[static_cast<size_t>(Keys::Printables::J)] = Keys::Modifiers::CMD;
    arr[static_cast<size_t>(Keys::Printables::F)] = Keys::Modifiers::CMD;

    return arr;
};

constexpr KeyBindingArray keyBindingArray{createKeyBindingArray()};
} // namespace AppDefaults
