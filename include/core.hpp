#ifndef CORE_HPP
#define CORE_HPP

#include "types.hpp"

class Core {
  private:
    eventCallback m_coreToPlatform{nullptr};

  public:
    Core();

    auto setEventCallback(eventCallback callback) -> void;
    auto eventCallback(const Event &event) -> void;
};

#endif // CORE_HPP
