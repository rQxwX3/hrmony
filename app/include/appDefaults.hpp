#ifndef APPDEFAULTS_HPP
#define APPDEFAULTS_HPP

#include <types.hpp>

namespace AppDefaults {

constexpr auto createKeyBindingArray() -> KeyBindingArray {
    KeyBindingArray arr{Keys::Modifiers::NULLKEY};

    arr[static_cast<size_t>(Keys::Printables::J)] = Keys::Modifiers::CMD;
    arr[static_cast<size_t>(Keys::Printables::F)] = Keys::Modifiers::CMD;
    arr[static_cast<size_t>(Keys::Printables::K)] = Keys::Modifiers::ALT;
    arr[static_cast<size_t>(Keys::Printables::D)] = Keys::Modifiers::ALT;
    arr[static_cast<size_t>(Keys::Printables::L)] = Keys::Modifiers::CTRL;
    arr[static_cast<size_t>(Keys::Printables::S)] = Keys::Modifiers::CTRL;
    arr[static_cast<size_t>(Keys::Printables::A)] = Keys::Modifiers::SHIFT;
    arr[static_cast<size_t>(Keys::Printables::SEMICOLON)] =
        Keys::Modifiers::SHIFT;

    return arr;
};

constexpr KeyBindingArray keyBindingArray{createKeyBindingArray()};
} // namespace AppDefaults

#endif // APPDEFAULTS_HPP
