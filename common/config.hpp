#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <appTypes.hpp>
#include <constants.hpp>
#include <keys.hpp>
#include <platformTypes.hpp>

namespace conf {
struct Config {
    key::Keys exitKey;

    plt::types::NativeCodeToKeyType nativeCodeToKey;
    plt::types::KeyToNativeCodeType keyToNativeCode;

    mac::types::ModifierToCGEventFlagsType modifierToCGEventFlags;
};

constexpr auto loadDefaultConfig() -> Config {
    mac::consts::createNativeCodeToKey();
    mac::consts::createKeyToNativeCode();
    mac::consts::createModifierToCGEventFlags();

    Config config{
        .exitKey = key::Keys::ESC,

        .nativeCodeToKey = plt::types::NativeCodeToKey,
        .keyToNativeCode = plt::types::KeyToNativeCode,

        .modifierToCGEventFlags = mac::types::ModifierToCGEventFlags,
    };

    return config;
}

const Config defaultConfig{loadDefaultConfig()};
} // namespace conf

#endif // CONFIG_HPP
