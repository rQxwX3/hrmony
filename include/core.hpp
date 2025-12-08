#ifndef CORE_HPP
#define CORE_HPP

#include "types.hpp"

class App;

class Core {
  private:
    App *sApp{nullptr};

  public:
    Core(App *app);

    auto onPlatformEvent(const Event &event) -> void;
};

#endif // CORE_HPP
