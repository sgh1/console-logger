
#include "logger_impl.h"

#include <ctime>
#include <cstdio>
#include <csignal>

namespace devlib
{

    logger_impl::logger_impl(){}
    logger_impl::~logger_impl() {}

    void logger_impl::debug(const char *msg) const 
    {
#ifdef _DEBUG
        non_error_msg(msg, "DEBUG");
#endif
    }

    void logger_impl::info(const char *msg) const {
        non_error_msg(msg, "INFO");
    }

    void logger_impl::warning(const char *msg) const {
        non_error_msg(msg, "WARN");
    }

    void logger_impl::error(const char *msg) const 
    {
        // Get the lock.
        std::lock_guard<std::mutex> lg(lock_);

        // Write message
        write_msg(msg, "ERROR");

        // Throw if exceptions, terminate otherwise.
#ifdef DEVLIB_WITH_EXCEPTIONS
        throw;
#else
        std::terminate();
#endif
    }

    void logger_impl::write_msg(const char *msg, const char *severity) const
    {
        // Create time string.
        char s[64];
        time_t t = time(NULL);
        struct tm *p = localtime(&t);
        strftime(s, 64, "%F::%T", p);

        // Print time, severity, and message.
        printf("%s", s);
        printf(" - [%-5s] - ", severity);
        printf("%s\n", msg);
    }

    void logger_impl::non_error_msg(const char* msg, const char* severity) const
    {
        // Get the lock.
        std::lock_guard<std::mutex> lg(lock_);

        // Write message
        write_msg(msg, severity);
    }

    // Get logger.
    const logger_impl& logger_impl::get_logger()
    {
        static logger_impl the_logger;
        return the_logger;
    }
}
