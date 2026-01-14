#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <appTypes.hpp>
#include <constants.hpp>
#include <keys.hpp>
#include <platformTypes.hpp>

namespace conf {
struct Config {
    key::Keys exitKey;

    plat::types::NativeCodeToKeyType nativeCodeToKey;
    plat::types::KeyToNativeCode keyToNativeCode;

    mac::types::ModifierToCGEventFlags modifierToCGEventFlags;
};

constexpr auto loadDefaultConfig() -> Config {
    mac::consts::createNativeCodeToKey();

    Config config{
        .exitKey = key::Keys::ESC,

        .nativeCodeToKey = plat::types::NativeCodeToKey,
        .keyToNativeCode = mac::consts::keyToNativeCode,

        .modifierToCGEventFlags = mac::consts::modifierToCGEventFlags,
    };

    return config;
}

const Config defaultConfig{loadDefaultConfig()};
} // namespace conf

#endif // CONFIG_HPP
