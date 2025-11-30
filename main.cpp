#include "include/app.hpp"

#include <iostream>
#include <unistd.h>

auto dummyEventSend(const Event &event) {
    std::cout << "hello from dummy!\n";
    return;
}

auto main() -> int {
    App app{App(dummyEventSend, dummyEventSend)};

    app.run();
}
