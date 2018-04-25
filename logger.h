
#ifndef BLOCK_MATRIX_ERR_H
#define BLOCK_MATRIX_ERR_H

#include <mutex>
#include <memory>

namespace devlib
{

    // Simple console logger.
    class logger_impl
    {
    public:

        // Constructor & destructor.
        logger_impl();
        ~logger_impl();

        // Logging functions.
        void debug(const char* msg) const;
        void info(const char* msg) const;
        void warning(const char* msg) const;
        void error(const char* msg) const;

        static const logger_impl* get_logger();

    private:

        // Helper to write messages.
        void write_msg(const char* msg, const char* severity) const;

        // Lock for multi-threaded logging.
        mutable std::mutex lock_;

        // Since we're only supporting console logging, only have one sink for now.
        static std::unique_ptr<logger_impl> the_logger_;

    };


    class logger
    {
    public:

        // Logging functions.
        static void debug(const char* msg);
        static void info(const char* msg);
        static void warning(const char* msg);
        static void error(const char* msg);

    private:

    };

}

#endif
