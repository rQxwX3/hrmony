#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <appDefaults.hpp>
#include <keys.hpp>
#include <types.hpp>

using Keys::Printables, Keys::Modifiers;

namespace Config {

struct Config {
    Modifiers m_leaderKey;
    Printables m_exitKey;
};

constexpr auto loadDefaultConfig() -> Config {
    Config config{.m_leaderKey = Modifiers::CMD, .m_exitKey = Printables::ESC};

    return config;
}

constexpr Config defaultConfig{loadDefaultConfig()};
} // namespace Config

#endif // CONFIG_HPP
