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

#ifdef __APPLE__
        .nativeCodeToKey = mac::consts::createNativeCodeToKey(),
        .keyToNativeCode = mac::consts::createKeyToNativeCode(),
        .modifierToCGEventFlags = mac::consts::createModifierToCGEventFlags(),
#endif
    };

    return config;
}

const Config defaultConfig{loadDefaultConfig()};
} // namespace conf

#endif // CONFIG_HPP
