#ifndef APPDEFAULTS_HPP
#define APPDEFAULTS_HPP

#include <combination.hpp>
#include <types.hpp>

namespace app {
inline auto createKeyBindingArray() -> KeyBindingArray {
    KeyBindingArray arr{Combination()};

    using key::Modifiers, key::Keys;

    arr[static_cast<size_t>(Keys::J)] = Combination(
        {Modifiers::CMD, Modifiers::ALT, Modifiers::CTRL, Modifiers::SHIFT}, 4);

    arr[static_cast<size_t>(Keys::A)] = Combination({Keys::S}, 1);

    // arr[static_cast<size_t>(Printables::K)] = {Modifiers::ALT};
    // arr[static_cast<size_t>(Printables::L)] = {Modifiers::CTRL};
    // arr[static_cast<size_t>(Printables::SEMICOLON)] =
    // {Keys::Modifiers::SHIFT};

    return arr;
};

const KeyBindingArray keyBindingArray{createKeyBindingArray()};
} // namespace app

#endif // APPDEFAULTS_HPP
