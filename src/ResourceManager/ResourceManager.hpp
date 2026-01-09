#pragma once

#include "../logger/logger.hpp"

#include <memory>
#include <string>
#include <vector>

namespace findit {

class ResourceManager {
public:
    ResourceManager(std::shared_ptr<Logger> &logger) : m_logger(logger) {} 

    [[nodiscard]] std::string loadShader(const std::string &path);
    [[nodiscard]] std::vector<float> loadModel(const std::string &path);

private:
    std::shared_ptr<Logger> m_logger;
};

}