#pragma once

#include <string>

namespace findit {

class Logger {
public:
    Logger() { log("[+] 'LOGGER' Logger has created", GREEN); };
    void log(const std::string &message, const char* type);

    static constexpr const char* RED = "\033[31m";
    static constexpr const char* GREEN = "\033[32m";
    static constexpr const char* YELLOW = "\033[33m";
    static constexpr const char* GRAY = "\033[90m";
    static constexpr const char* RESET = "\033[0m";

};

}