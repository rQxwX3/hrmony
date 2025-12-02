#include <utility>

#include "../include/core.hpp"

Core::Core() = default;

auto Core::setEventCallback(::eventCallback callback) -> void {
    m_coreToPlatform = std::move(callback);
}

auto Core::eventCallback(const Event &event) -> void {
    m_coreToPlatform(event);
}
