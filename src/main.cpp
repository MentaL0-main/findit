#include "core/application.hpp"
#include "logger/logger.hpp"

#include <exception>
#include <memory>

int main() {
    std::shared_ptr<findit::Logger> logger = std::make_shared<findit::Logger>();
    std::unique_ptr<findit::Application> app = std::make_unique<findit::Application>(logger);

    try {
        app->run();
    } catch (std::exception &error) {
        logger->log(error.what(), logger->RED);
        return 1;
    }

    return 0;
}