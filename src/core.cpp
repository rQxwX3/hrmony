#include "../include/core.hpp"
#include "../include/app.hpp"

#include <vector>

Core::Core(App *appPtr) : m_appPtr{appPtr} { m_keyMaps[Key::A] = {Key::S}; }

auto Core::getRemappedKeys(const Key key) -> std::vector<Key> {
    if (m_keyMaps.find(key) == m_keyMaps.end()) {
        return {key};
    }

    return m_keyMaps[key];
}

auto Core::onPlatformEvent(const Event &event) -> void {
    const std::vector<Key> &eventKeys{event.getKeys()};

    std::vector<Key> remappedEventKeys;

    for (const auto &key : eventKeys) {
        const std::vector<Key> remappedKeys{getRemappedKeys(key)};

        for (const auto &remappedKey : remappedKeys) {
            remappedEventKeys.push_back(remappedKey);
        }
    }

    m_appPtr->sendEventToPlatform({remappedEventKeys});

    // const std::vector<Key> &eventKeys{event.getKeys()};
    //
    // std::vector<Key> newEventKeys;
    //
    // for (const auto &key : eventKeys) {
    //     const std::vector<Key> &remappedKeys{m_keyMaps.at(key)};
    //
    //     for (const auto &newKey : remappedKeys) {
    //         newEventKeys.push_back(newKey);
    //     }
    // }
    //
    // m_appPtr->sendEventToPlatform({newEventKeys});
}
