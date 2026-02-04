#include <app.hpp>
#include <logger.hpp>

auto main() -> int {
    app::App app;

    app::App::loadConfig();

    app.run();
}
