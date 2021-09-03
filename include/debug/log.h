#include <core.h>

namespace ZWET
{
    class Log
    {   
        public:
            Log();

            ~Log();

            static UniquePtr<Log> createLogService();

            void info(std::string message);

            void error(std::string message);

            void message(std::string message);

            void warn(std::string message);
    };
}

// logging service
#define ZWET_INFO(...) ::ZWET::Log::createLogService()->info(__VA__ARGS__)
#define ZWET_ERROR(...) ::ZWET::Log::createLogService()->error(__VA__ARGS__)
#define ZWET_MESSAGE(...) ::ZWET::Log::createLogService()->message(__VA__ARGS__)
#define ZWET_WARN(...) ::ZWET::Log::createLogService()->warn(__VA__ARGS__)