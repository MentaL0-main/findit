#pragma once

#include <string>

namespace findit {

class ResourceManager {
public:
    ResourceManager() = default;

    [[nodiscard]] std::string loadShader(const std::string &path);

private:

};

}