#include <log.h>

namespace ZWET
{
    Log::Log()
    {
        ;
    }

    Log::~Log()
    {
        ;
    }

    UniquePtr<Log> Log::createLogService()
    {
        return CreateUnique<Log>();
    }

    void Log::info(std::string message)
    {
        std::cout << "::INFO::" << message << std::endl;
    }

    void Log::error(std::string message)
    {
        std::cout << "::ERROR::" << message << std::endl;
    }

    void Log::message(std::string message)
    {
        std::cout << "::MESSAGE::" << message << std::endl;
    }

    void Log::warn(std::string message)
    {
        std::cout << "::WARNING::" << message << std::endl;
    }
}