#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <appDefaults.hpp>
#include <combination.hpp>
#include <constants.hpp>
#include <keys.hpp>
#include <types.hpp>

using Keys::Printables, Keys::Modifiers, macOS::constants::nativeKeyToPrintable,
    macOS::constants::modifierToNativeModifier,
    macOS::constants::printableToNativeKey, ::AppDefaults::keyBindingArray;

namespace conf {
struct Config {
    Modifiers leaderKey;
    Printables exitKey;

    NativeKeyToPrintable nativeKeyToPrintable;
    PrintableToNativeKey printableToNativeKey;
    ModifierToNativeModifier modifierToNativeModifier;

    KeyBindingArray keyBindingArray;
};

constexpr auto loadDefaultConfig() -> Config {
    Config config{.leaderKey = Modifiers::CMD,
                  .exitKey = Printables::ESC,
                  .nativeKeyToPrintable = nativeKeyToPrintable,
                  .printableToNativeKey = printableToNativeKey,
                  .modifierToNativeModifier = modifierToNativeModifier,
                  .keyBindingArray = keyBindingArray};

    return config;
}

const Config defaultConfig{loadDefaultConfig()};
} // namespace conf

#endif // CONFIG_HPP
