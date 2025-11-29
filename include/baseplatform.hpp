#ifndef BASEPLATFORM_HPP
#define BASEPLATFORM_HPP

#include "iplatform.hpp"
#include "types.hpp"

class BasePlatform : public IPlatform {
  public:
    static inline HRMModeToggleCallback sHRMModeEnterCallback{nullptr};

    BasePlatform() = default;
};

#endif // BASEPLATFORM_HPP
