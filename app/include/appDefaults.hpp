#ifndef APPDEFAULTS_HPP
#define APPDEFAULTS_HPP

#include <types.hpp>

namespace AppDefaults {
constexpr auto createKeyBindingArray() -> KeyBindingArray {
    KeyBindingArray arr{Keys::Modifiers::NULLKEY};

    using Keys::Modifiers, Keys::Printables;

    arr[static_cast<size_t>(Printables::J)] = {
        Modifiers::CMD, Modifiers::ALT, Modifiers::CTRL, Modifiers::SHIFT};

    arr[static_cast<size_t>(Printables::K)] = {Modifiers::ALT};
    arr[static_cast<size_t>(Printables::L)] = {Modifiers::CTRL};
    arr[static_cast<size_t>(Printables::SEMICOLON)] = {Keys::Modifiers::SHIFT};

    return arr;
};

constexpr KeyBindingArray keyBindingArray{createKeyBindingArray()};
} // namespace AppDefaults

#endif // APPDEFAULTS_HPP
