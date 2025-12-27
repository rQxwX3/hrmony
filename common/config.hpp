#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <appDefaults.hpp>
#include <combination.hpp>
#include <constants.hpp>
#include <keys.hpp>
#include <types.hpp>

using key::Modifiers, key::Keys, macOS::constants::nativeCodeToKey,
    macOS::constants::keyToNativeCode, macOS::constants::modifierToNativeCode,
    macOS::constants::modifierToCGEventFlags,
    macOS::constants::nativeCodeToModifier, macOS::types::NativeCodeToModifier,
    macOS::types::ModifierToCGEventFlags, ::app::keyBindingArray;

namespace conf {
struct Config {
    Modifiers leaderKey;
    Keys exitKey;

    NativeCodeToKey nativeCodeToKey;
    KeyToNativeCode keyToNativeCode;

    ModifierToCGEventFlags modifierToCGEventFlags;
    ModifierToNativeCode modifierToNativeCode;

    NativeCodeToModifier nativeCodeToModifier;

    KeyBindingArray keyBindingArray;
};

constexpr auto loadDefaultConfig() -> Config {
    Config config{.leaderKey = Modifiers::RIGHT_CMD,
                  .exitKey = Keys::ESC,

                  .nativeCodeToKey = nativeCodeToKey,
                  .keyToNativeCode = keyToNativeCode,

                  .modifierToCGEventFlags = modifierToCGEventFlags,
                  .modifierToNativeCode = modifierToNativeCode,

                  .nativeCodeToModifier = nativeCodeToModifier,

                  .keyBindingArray = keyBindingArray};

    return config;
}

const Config defaultConfig{loadDefaultConfig()};
} // namespace conf

#endif // CONFIG_HPP
