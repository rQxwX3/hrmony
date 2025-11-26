#include "./app/include/app.hpp"
#include "./platform/linux/include/linuxPlatform.hpp"
#include "./platform/mac/include/macPlatform.hpp"
#include "./platform/win/include/winPlatform.hpp"

#include <iostream>
#include <memory>

auto main() -> int {
    // std::unique_ptr<IPlatform> platform = nullptr;

    // #ifdef _WIN32
    //     platform = new WinPlatform();
    // #elif __APPLE__
    //     platform = std::make_unique<MacPlatform>();
    // #elif __linux__
    //     platform = new LinuxPlatform();
    // #endif

    std::cout << "hello, hrmony\n";
}
