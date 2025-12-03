#ifndef CORE_HPP
#define CORE_HPP

#include "types.hpp"

class App;

class Core {
  private:
    static inline const App *sApp{nullptr};
    static inline const eventCallback sCoreToPlatform{nullptr};

  public:
    Core(const App *app);
};

#endif // CORE_HPP
