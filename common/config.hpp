#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <constants.hpp>
#include <keys.hpp>
#include <types.hpp>

using Keys::Printables, Keys::Modifiers, macOS::constants::nativeKey2Printable,
    macOS::constants::modifier2NativeModifier,
    macOS::constants::printable2NativeKey;

namespace conf {
struct Config {
    Modifiers leaderKey;
    Printables exitKey;

    NativeKey2PrintableArray nativeKey2Printable;
    Printable2NativeKeyArray printable2NativeKey;
    Modifier2NativeModifierArray modifier2NativeModifier;
};

constexpr auto loadDefaultConfig() -> Config {
    Config config{.leaderKey = Modifiers::CMD,
                  .exitKey = Printables::ESC,
                  .nativeKey2Printable = nativeKey2Printable,
                  .printable2NativeKey = printable2NativeKey,
                  .modifier2NativeModifier = modifier2NativeModifier};

    return config;
}

constexpr Config defaultConfig{loadDefaultConfig()};
} // namespace conf

#endif // CONFIG_HPP
