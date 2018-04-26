
#ifndef CLOGGER_H
#define CLOGGER_H

namespace devlib
{
    class logger
    {
    public:

        // Logging functions.
        static void debug(const char* msg);
        static void info(const char* msg);
        static void warning(const char* msg);
        static void error(const char* msg);
    };
}

#endif
