#include "ResourceManager.hpp"

#include <charconv>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace findit {

std::string ResourceManager::loadShader(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("[!] 'RESOURCE MANAGER' Failed to read shader file: " + path);
    }

    m_logger->log("[+] 'RESORCE MANAGER' Open file: " + path, m_logger->GREEN);
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string result = buffer.str();
    
    m_logger->log("[+] 'RESORCE MANAGER' Read file: " + path, m_logger->GREEN);

    return result;
}
std::vector<float> ResourceManager::loadModel(const std::string &path) {
    std::vector<float> vertices;
    
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("[!] Failed to read shader file: " + path);
    }

    m_logger->log("[+] 'RESORCE MANAGER' Open file: " + path, m_logger->GREEN);

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string result = buffer.str();

    m_logger->log("[+] 'RESORCE MANAGER' Read file: " + path, m_logger->GREEN);

    const char* ptr = result.data();
    const char* end = result.data() + result.size();

    while (ptr < end) {
        while (ptr < end && (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')) ++ptr;
        if (ptr >= end) break;
        
        float value;
        auto [new_ptr, ec] = std::from_chars(ptr, end, value);
        
        if (ec == std::errc()) {
            vertices.push_back(value);
            ptr = new_ptr;
        } else {
            break;
        }
    }

    m_logger->log("[+] 'RESORCE MANAGER' Download model: " + path, m_logger->GREEN);

    return vertices;
}

}