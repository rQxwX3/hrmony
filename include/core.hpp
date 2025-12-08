#ifndef CORE_HPP
#define CORE_HPP

#include "types.hpp"

class App;

class Core {
  private:
    App *m_appPtr{nullptr};

  public:
    Core(App *appPtr);

    auto onPlatformEvent(const Event &event) -> void;
};

#endif // CORE_HPP
