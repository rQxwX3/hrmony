#include "../include/core.hpp"
#include "../include/app.hpp"

#include <iostream>
#include <vector>

Core::Core(App *appPtr) : m_appPtr{appPtr} {
    m_keyMaps[Key::A] = {Key::A, Key::B, Key::C};
}

auto Core::onPlatformEvent(const Event &event) -> void {
    const std::vector<Key> &eventKeys{event.getKeys()};

    std::vector<Key> newEventKeys;

    for (const auto &key : eventKeys) {
        const std::vector<Key> &remappedKeys{m_keyMaps.at(key)};

        for (const auto &newKey : remappedKeys) {
            newEventKeys.push_back(newKey);
        }
    }

    m_appPtr->sendEventToPlatform({newEventKeys});

    std::cout << "hello from core\n";
}
