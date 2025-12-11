#include "../include/app.hpp"
#include "../include/macos.hpp"

#include <memory>

App::App() : m_platform{std::make_unique<MacOS>(this)} {}

auto App::run() -> void {
    m_running = true;
    m_platform->run();
}

auto App::isRunning() const -> bool { return m_running; }

auto App::isHRMMode() const -> bool { return m_HRMMode; }

auto App::getRemappedKeys(const Key key) -> Key {
    return m_keyBindingArray.at(static_cast<size_t>(key));
}

auto App::onPlatformEvent(const Event &event) -> void {
    const std::vector<Key> &eventKeys{event.getKeys()};

    sendEventToPlatform({{getRemappedKeys(eventKeys.at(0))}});

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
auto App::sendEventToPlatform(const Event &event) -> void {
    toggleHRMMode();
    m_platform->onAppEvent(event);
}

auto App::toggleHRMMode() -> void { m_HRMMode = !m_HRMMode; }
