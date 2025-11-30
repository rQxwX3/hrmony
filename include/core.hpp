#ifndef CORE_HPP
#define CORE_HPP

#include "types.hpp"

class Core {
  private:
    sendEventCallback m_coreToPlatform;

  public:
    Core(sendEventCallback coreToPlatform);
};

#endif // CORE_HPP
