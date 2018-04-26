
#include "logger_impl.h"
#include "logger.h"

namespace devlib
{
    void logger::debug(const char *msg) {
        logger_impl::get_logger().debug(msg);
    }

    void logger::info(const char *msg) {
        logger_impl::get_logger().info(msg);
    }

    void logger::warning(const char *msg) {
        logger_impl::get_logger().warning(msg);
    }

    void logger::error(const char *msg) {
        logger_impl::get_logger().error(msg);
    }
}


