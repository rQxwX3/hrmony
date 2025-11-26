#ifndef APP_HPP
#define APP_HPP

#include "../../core/include/iplatform.hpp"

class App {
  private:
    bool isRunning;
    IPlatform *platform;

  public:
    App(IPlatform *platform) : isRunning(false), platform(platform) {}
};

#endif // APP_HPP
