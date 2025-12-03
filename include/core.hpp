#ifndef CORE_HPP
#define CORE_HPP

#include "types.hpp"

class App;

class Core {
  private:
    eventCallback m_coreToPlatform{nullptr};
    static inline const App *sApp{nullptr};

  public:
    Core(const App *app);

    auto setEventCallback(eventCallback callback) -> void;
    auto eventCallback(const Event &event) -> void;
};

#endif // CORE_HPP
