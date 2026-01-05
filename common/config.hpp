#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <appTypes.hpp>
#include <constants.hpp>
#include <keys.hpp>
#include <platformTypes.hpp>

namespace conf {
struct Config {
    key::Keys leaderKey;
    key::Keys exitKey;

    plat::types::NativeCodeToKey nativeCodeToKey;
    plat::types::KeyToNativeCode keyToNativeCode;

    mac::types::ModifierToCGEventFlags modifierToCGEventFlags;

    app::types::Groups groups;
};

constexpr auto loadDefaultConfig() -> Config {
    Config config{
        .leaderKey = key::Keys::RIGHT_CMD,
        .exitKey = key::Keys::ESC,

        .nativeCodeToKey = mac::consts::nativeCodeToKey,
        .keyToNativeCode = mac::consts::keyToNativeCode,

        .modifierToCGEventFlags = mac::consts::modifierToCGEventFlags,

        .groups = app::types::createGroups(),
    };

    return config;
}

const Config defaultConfig{loadDefaultConfig()};
} // namespace conf

#endif // CONFIG_HPP
