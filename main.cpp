#include <app.hpp>

#include <logger.hpp>

auto main() -> int {
    app::App app;

    // log::Logger logger("log/", "log.txt");
    // logger.log("this is a test message", log::MessageLevel::INFO);

    app.run();
}
