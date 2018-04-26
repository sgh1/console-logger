
#ifndef LOGGER_IMPL_H
#define LOGGER_IMPL_H

#include <mutex>

namespace devlib
{
    // Simple console logger.
    class logger_impl
    {
    public:

        // Constructor & destructor.
        logger_impl();
        ~logger_impl();

        // Don't allow copies.
        logger_impl(logger_impl const& copy) = delete;
        logger_impl& operator=(logger_impl const& copy) = delete;

        // Logging functions.
        void debug(const char* msg) const;
        void info(const char* msg) const;
        void warning(const char* msg) const;
        void error(const char* msg) const;

        static const logger_impl& get_logger();

    private:

        // Helpers to write messages.
        void write_msg(const char* msg, const char* severity) const;
        void non_error_msg(const char* msg, const char* severity) const;

        // Lock for multi-threaded logging.
        mutable std::mutex lock_;
    };
}

#endif
