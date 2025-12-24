#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <constants.hpp>
#include <keys.hpp>
#include <types.hpp>

using Keys::Printables, Keys::Modifiers, macOS::constants::nativeKey2Printable,
    macOS::constants::modifier2NativeModifier;

namespace conf {
struct Config {
    Modifiers leaderKey;
    Printables exitKey;

    NativeKey2PrintableArray nativeKey2Printable;
    Modifier2NativeModifierArray modifier2NativeModifier;
};

constexpr auto loadDefaultConfig() -> Config {
    Config config{.leaderKey = Modifiers::CMD,
                  .exitKey = Printables::ESC,
                  .nativeKey2Printable = nativeKey2Printable,
                  .modifier2NativeModifier = modifier2NativeModifier};

    return config;
}

constexpr Config defaultConfig{loadDefaultConfig()};
} // namespace conf

#endif // CONFIG_HPP
