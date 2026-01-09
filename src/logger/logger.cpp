#include "logger.hpp"

#include <iostream>

namespace findit {

void Logger::log(const std::string &message, const char* type) {
    std::cout << type << message << RESET << std::endl;
}

}