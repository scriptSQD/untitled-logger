#pragma once

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "Timestamper.hpp"

#include "fmt/format.h"

namespace SQD {

/**
 * It is preferred to use macros instead of direct invocation if you want to
 * strip logging completely in, e.g., Release builds.
 */
#ifndef SQD_DISABLE_LOGGER
#define SQD_LOG(...) SQD::Logger::Log(fmt::format(__VA_ARGS__))
#define SQD_WARN(...) SQD::Logger::Log(fmt::format(__VA_ARGS__), SQD::Logger::LEVEL_WARNING)
#define SQD_ERR(...) SQD::Logger::Log(fmt::format(__VA_ARGS__), SQD::Logger::LEVEL_ERROR)
#elif SQD_DISABLE_LOGGER == 1
#define SQD_LOG(...)
#define SQD_WARN(...)
#define SQD_ERR(...)
#endif

    namespace fs = std::filesystem;

    class Logger {
    public:
        /**
         * Specify the level of log entry.
         * LOG - is a regular debug statement, not indicating any problems.
         * WARNING - something went not as planned, but didn't cause serious mess.
         * ERROR - when program has to terminate because of some problem.
         */
        enum LogLevel {
            LEVEL_LOG = 1, LEVEL_WARNING = 2, LEVEL_ERROR = 3
        };

        Logger();

        explicit Logger(const fs::path &debugFilePath);

        ~Logger();

        /**
         * Initializes debug file to write into.
         * @param path Opens std::ofstream at the given path for write.
         */
        static void InitDebugToFile(const fs::path &path);

        // Syntactic sugar
        /**
         * Syntactic sugar to set logger state to enabled.
         * @param enable Whether to enable logger.
         */
        static void EnableLogger(bool enable = true);

        /**
         * Syntactic sugar to set logger state to disabled.
         * @param disable Whether to disable logger.
         */
        static void DisableLogger(bool disable = true);

        /**
         * Syntactic sugar to enable writing debug info to file. You should also set
         * debug file if not already, so that logger has somewhere to write to.
         * @param enable Whether to enable debugging to file.
         */
        static void EnableDebugToFile(bool enable = true);

        /**
         * Syntactic sugar to enable writing debug info to file. You should also set
         * debug file if not already, so that logger has somewhere to write to.
         * @param disable
         */
        static void DisableDebugToFile(bool disable = true);

        /**
         * Do not mirror debug log to stdout if debugging to file.
         * @param enable Whether to enable no stdout.
         */
        static void EnableNoStdout(bool enable = true);

        /**
         * Do not mirror debug log to stdout if debugging to file.
         * @param disable Whether to disable no stdout.
         */
        static void DisableNoStdout(bool disable = true);

        /**
         * Opens given path as current debug file.
         * All subsequent logs will be written to the file at given path.
         * @param path Opens std::ofstream at the given path for write.
         */
        static void SetDebugFile(const fs::path &path);

        /**
         * Log method uses class' internal state
         * to log either to file, to stdout, both or nowhere.
         *
         * @param message Gets printed to the logging destination.
         * @param prefix Is optional, this is appended as logging level prefix (like
         * LOG, WARNING, ERROR, etc.)
         */
        static void Log(std::string_view message,
                        const LogLevel &level = LEVEL_LOG);

    private:
        static void Handle(std::string_view message,
                           std::ofstream::failure &error);

        static void LogToFile(std::string_view message,
                              const LogLevel &level = LEVEL_LOG);

        static void LogToStdout(std::string_view message,
                                const LogLevel &level = LEVEL_LOG);

        inline static bool ToFile = false;
        inline static bool NoStdout = false;
        inline static bool LoggerEnabled = false;

        inline static constexpr std::string_view COLOR_ESCAPE = "\033[0m";

        inline static const std::unordered_map<LogLevel, std::string_view>
                LogLevelPrefixes = {{LEVEL_LOG,     "LOG"},
                                    {LEVEL_WARNING, "WARNING"},
                                    {LEVEL_ERROR,   "ERROR"}};
        inline static const std::unordered_map<LogLevel, std::string_view>
                LogLevelColors = {{LEVEL_LOG,     "\033[37m"},
                                  {LEVEL_WARNING, "\033[33m"},
                                  {LEVEL_ERROR,   "\033[31m"}};

        static const auto OpenMode =
                std::ios::out | std::ios::binary | std::ios::app;
        inline static std::unique_ptr<std::ofstream> debugFile =
                std::make_unique<std::ofstream>();
    };
} // namespace SQD
