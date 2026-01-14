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
    plat::types::KeyToNativeCodeType keyToNativeCode;

    mac::types::ModifierToCGEventFlags modifierToCGEventFlags;
};

constexpr auto loadDefaultConfig() -> Config {
    mac::consts::createNativeCodeToKey();
    mac::consts::createKeyToNativeCode();

    Config config{
        .exitKey = key::Keys::ESC,

        .nativeCodeToKey = plat::types::NativeCodeToKey,
        .keyToNativeCode = plat::types::KeyToNativeCode,

        .modifierToCGEventFlags = mac::consts::modifierToCGEventFlags,
    };

    return config;
}

const Config defaultConfig{loadDefaultConfig()};
} // namespace conf

#endif // CONFIG_HPP
