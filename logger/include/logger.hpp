#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string_view>

namespace log {
enum class MessageLevel : uint8_t {
    INFO = 0,
    ERROR,
    WARN,
    m_size,
};

constexpr std::array<std::string_view,
                     static_cast<size_t>(MessageLevel::m_size)>
    messagePrefixes{"INFO", "ERROR", "WARN"};

class Logger {
  private:
    std::ofstream m_logfile;

  public:
    Logger(const std::filesystem::path &logDirectory,
           const std::string_view &logFile);

    auto log(const std::string_view &svMessage, MessageLevel messageLevel)
        -> void;
};
} // namespace log

#endif // LOGGER_HPP
