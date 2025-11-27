#include "include/event.hpp"
#include "include/iplatform.hpp"
#include "include/macos.hpp"

#include <memory>
#include <unistd.h>

auto main() -> int {
    Event aDown{Key::A, true};
    Event aUp{Key::A, false};

    std::unique_ptr<IPlatform> platform{std::make_unique<MacOS>()};

    platform->sendEvent(aDown);
    usleep(500);
    platform->sendEvent(aUp);
}
