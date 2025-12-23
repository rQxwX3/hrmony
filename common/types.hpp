#ifndef TYPES_HPP
#define TYPES_HPP

#include <array>
#include <keys.hpp>

#ifdef __APPLE__
#include <macosTypes.hpp>
#endif // __APPLE__

using NativeKey2PrintableArray = std::array<Keys::Printables, maxKeyCode>;

using Modifier2NativeModifierArray =
    std::array<NativeModifier, static_cast<size_t>(Keys::Modifiers::m_size)>;

using ModifiersArray = std::array<Keys::Modifiers, maxModifierCnt>;

using KeyBindingArray =
    std::array<ModifiersArray, static_cast<size_t>(Keys::Printables::m_size)>;

using CurrentModifiersArray = std::array<Keys::Modifiers, maxModifierCnt>;

#endif // TYPES_HPP
