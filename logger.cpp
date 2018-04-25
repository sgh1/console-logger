
#include "logger.h"

#include <ctime>
#include <cstdio>
#include <csignal>

namespace devlib
{

    // Create the logger.
    std::unique_ptr<logger_impl> logger_impl::the_logger_;

    logger_impl::logger_impl() {
    }

    logger_impl::~logger_impl()
    {
        // Acquire the lock before destroying.
        std::lock_guard<std::mutex> lg(lock_);
    }

    void logger_impl::debug(const char *msg) const {

#ifdef _DEBUG

        // Get the lock.
        std::lock_guard<std::mutex> lg(lock_);

        // Write message
        write_msg(msg, "DEBUG");

#endif

    }

    void logger_impl::info(const char *msg) const {
        // Get the lock.
        std::lock_guard<std::mutex> lg(lock_);

        // Write message
        write_msg(msg, "INFO");
    }

    void logger_impl::warning(const char *msg) const {
        // Get the lock.
        std::lock_guard<std::mutex> lg(lock_);

        // Write message
        write_msg(msg, "WARN");
    }

    void logger_impl::error(const char *msg) const {
        // Get the lock.
        std::lock_guard<std::mutex> lg(lock_);

        // Write message
        write_msg(msg, "ERROR");

        // Throw an exception or terminate.
#ifdef DEVLIB_THROW_ERROR
        throw std::runtime_exception(msg);
#else
        // Generate an interrupt
        std::raise(SIGABRT);
        //std::terminate();
#endif

    }

    void logger_impl::write_msg(const char *msg, const char *severity) const {
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

    const logger_impl* logger_impl::get_logger()
    {
        // Create a logger_impl if there is none.
        if (logger_impl::the_logger_ == nullptr) {
            logger_impl::the_logger_ = std::unique_ptr<logger_impl>(new logger_impl);
        }

        // Return the logger backend.
        return logger_impl::the_logger_.get();
    }


    void logger::debug(const char *msg) {
        logger_impl::get_logger()->debug(msg);
    }

    void logger::info(const char *msg) {
        logger_impl::get_logger()->info(msg);
    }

    void logger::warning(const char *msg) {
        logger_impl::get_logger()->warning(msg);
    }

    void logger::error(const char *msg) {
        logger_impl::get_logger()->error(msg);
    }

}

