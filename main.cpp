#include "include/app.hpp"

#include <unistd.h>

auto main() -> int {
    App app{App()};

    app.run();
}
