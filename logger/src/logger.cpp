#include <logger.hpp>

#include <filesystem>
#include <fstream>

using log::Logger;

Logger::Logger(const std::filesystem::path &logDirectory,
               const std::string_view &logFile) {
    std::filesystem::create_directories(logDirectory);
    std::filesystem::path logFilePath{logDirectory / logFile};

    m_logfile.open(logFilePath, std::ios::app);

    if (!m_logfile.is_open()) {
        throw std::runtime_error("Logger: failed to open log file");
    }
}

auto getMessageLevelSV(log::MessageLevel messageLevel) {
    return log::messagePrefixes.at(static_cast<size_t>(messageLevel));
}

auto Logger::log(const std::string_view &svMessage, MessageLevel messageLevel)
    -> void {
    m_logfile << getMessageLevelSV(messageLevel) << ": " << svMessage << '\n';

    std::flush(m_logfile);
}
