#ifndef __M_LEVEL_H__
#define __M_LEVEL_H__

namespace lwlog{
    class Loglevel{
        public:
            enum class level{
                unknown=0,
                DEBUG,
                INFO,
                WARNING,
                ERROR,
                FATAL
            };
            static const char* to_string(level value)
            {
                switch(value)
                {
                    case level::DEBUG:return "DEBUG";
                    case level::INFO:return "INFO";
                    case level::WARNING:return "WARNING";
                    case level::ERROR:return "ERROR";
                    case level::FATAL:return "FATAL";
                    default:return "UNKNOWN";
                }
            } 
};
}

#endif