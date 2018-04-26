#include "logger.h"
#include "format.h"

#include <stdexcept>


int main()
{
    try
    {
        devlib::logger::info("Starting test program.");
        devlib::logger::info(devlib::format("There are ", 6, " eggs in the basket.").str().c_str());
        devlib::logger::warning("Something went a little wrong.");

        throw std::runtime_error("uh oh");
    }
    catch(const std::exception& e)
    {
        devlib::logger::error("Something went more wrong.");
    }

    return 0;
}