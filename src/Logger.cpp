#include <Logger.hpp>

SQD::Logger::Logger() = default;
SQD::Logger::Logger(const fs::path &debugFilePath) {
    Logger::InitDebugToFile(debugFilePath);
}

void SQD::Logger::InitDebugToFile(const fs::path &path) {
    try {
        Logger::debugFile->open(path, OpenMode);
    } catch (std::ofstream::failure &error) {
        Logger::Handle("Failed to open file at " + path.string() +
                           ".\nError output: " + error.what(),
                       error);
    }
}

void SQD::Logger::SetDebugFile(const fs::path &path) {
    if (!Logger::debugFile->is_open()) {
        Logger::debugFile->open(path, OpenMode);
    } else {
        Logger::debugFile->close();
        Logger::SetDebugFile(path);
    }
}

SQD::Logger::~Logger() {
    // Close all streams and stuff
    // that possibly causes headaches
    Logger::debugFile->close();
}

void SQD::Logger::EnableLogger(bool enable) { Logger::LoggerEnabled = enable; }
void SQD::Logger::EnableDebugToFile(bool enable) { Logger::ToFile = enable; }
void SQD::Logger::EnableNoStdout(bool enable) { Logger::NoStdout = enable; }

void SQD::Logger::DisableLogger(bool disable) {
    Logger::LoggerEnabled = !disable;
}
void SQD::Logger::DisableDebugToFile(bool disable) {
    Logger::ToFile = !disable;
}
void SQD::Logger::DisableNoStdout(bool disable) { Logger::NoStdout = !disable; }

void SQD::Logger::Handle(const std::string &message,
                         std::ofstream::failure &error) {
    Logger::LogToStdout(message, "ERROR");
    throw error;
}

void SQD::Logger::Log(const std::string &message, const std::string &prefix) {
    if (!Logger::LoggerEnabled) {
        return;
    }

    if (Logger::ToFile) {
        Logger::LogToFile(message, prefix);
    } else {
        Logger::LogToStdout(message, prefix);
    }
}

void SQD::Logger::LogToStdout(const std::string &message,
                              const std::string &prefix) {
    std::cout << COLOR_GRAY << Timestamper::GetCurrent() << " [" << prefix
              << "]: " << message << COLOR_ESCAPE << std::endl;
}

void SQD::Logger::LogToFile(const std::string &message,
                            const std::string &prefix) {
    try {
        (*Logger::debugFile) << Timestamper::GetCurrent() << " [" << prefix
                             << "]: " << message << std::endl;
    } catch (std::ofstream::failure &error) {
        Logger::Handle(static_cast<std::string>(
                           "Failed to write to debug file.\nError output: ")
                           .append(error.what()),
                       error);
    }

    if (!Logger::NoStdout) {
        Logger::LogToStdout(message, prefix);
    }
}
