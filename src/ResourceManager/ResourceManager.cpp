#include "ResourceManager.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace findit {

std::string ResourceManager::loadShader(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("[!] Failed to read shader file: " + path);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string result = buffer.str();
    
    return result;
}

}