#ifndef TYPES_HPP
#define TYPES_HPP

#include "event.hpp"

#include <functional>

using sendEventCallback = std::function<void(const Event &event)>;

#endif // TYPES_HPP
