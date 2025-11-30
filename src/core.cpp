#include <utility>

#include "../include/app.hpp"
#include "../include/core.hpp"
#include "../include/event.hpp"

Core::Core(sendEventCallback coreToPlatform)
    : m_coreToPlatform{std::move(coreToPlatform)} {}
