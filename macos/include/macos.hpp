#ifndef MACOS_HPP
#define MACOS_HPP

#include <app.hpp>
#include <combination.hpp>
#include <platform.hpp>

#include <ApplicationServices/ApplicationServices.h>
#include <optional>

namespace mac {
class MacOS : public plt::Platform {
  private:
    CFRunLoopRef m_runLoopRef;

  public:
    MacOS(grp::Group *groupPtr, app::App *appPtr);
    auto run() -> void override;
    ~MacOS() override;

  public:
    [[nodiscard]] auto modifierToCGEventFlags(key::Keys modifier) const
        -> std::optional<CGEventFlags>;

  public:
    MacOS(const MacOS &other) = delete;
    MacOS(MacOS &&other) = delete;

    auto operator=(const MacOS &other) -> MacOS & = delete;
    auto operator=(MacOS &&other) -> MacOS & = delete;
};
} // namespace mac

#endif // MACOS_HPP
