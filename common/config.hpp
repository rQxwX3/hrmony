#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <appDefaults.hpp>
#include <keys.hpp>
#include <macosConstants.hpp>
#include <types.hpp>

using Keys::Printables, Keys::Modifiers, MacOSConstants::nativeKey2Printable,
    MacOSConstants::modifier2NativeModifier;

namespace Config {

struct Config {
    Modifiers m_leaderKey;
    Printables m_exitKey;

    NativeKey2PrintableArray m_nativeKey2Printable;
    Modifier2NativeModifierArray m_modifier2NativeModifier;
};

constexpr auto loadDefaultConfig() -> Config {
    Config config{.m_leaderKey = Modifiers::CMD,
                  .m_exitKey = Printables::ESC,
                  .m_nativeKey2Printable = nativeKey2Printable,
                  .m_modifier2NativeModifier = modifier2NativeModifier};

    return config;
}

constexpr Config defaultConfig{loadDefaultConfig()};
} // namespace Config

#endif // CONFIG_HPP
