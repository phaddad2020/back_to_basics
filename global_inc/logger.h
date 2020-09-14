/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Global utility logger                               *
 *                                                                  *
 *******************************************************************/

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <sstream>

#define BLOG_INITIALISE(level) eLoggerLevel Logger::LoggerLevel = level;

#define BLOG_SETLEVEL(level)   Logger::LoggerLevel = level
#define BLOG(level)            if (level > Logger::LoggerLevel) ; \
                                else Logger(level)

/// <summary>
// The following enum describes the different possible levels of logging
// </summary>
typedef enum loggerLevel_e
{
    eLogError       = 0,        // Only show errors
    eLogWarning,                // Show warnings and errors
    eLogInfo,                    // Show info, warnings and errors
    eLogDebug,                  // Show debug, info, warnings and errors
} eLoggerLevel;

/// <summary>
// The following Logger class performs stream output and is designed
// as an object which is to be instantiated and destroyed upon use.
// The best way to use this class is with the define MACROS above
// </summary>
class Logger
{
public:

    static eLoggerLevel LoggerLevel;

    // Default Constructor
    Logger() { };

    // Initialisation Constructor
    Logger(eLoggerLevel loggerLevel = eLogError)
    {
        data_buffer << ConvertLevelToString(loggerLevel) << " ";
    }

    // Destructor
    ~Logger()
    {
        data_buffer << std::endl;
        std::cerr << data_buffer.str();
    }

    std::string ConvertLevelToString(eLoggerLevel loggerLevel)
    {
        switch (loggerLevel)
        {
            case eLogError:
                return "\e[1;31m[ERROR]:\e[0m";
            case eLogWarning:
                return "\e[1;33m[WARNING]:\e[0m";
            case eLogDebug:
                return "\e[1;36m[DEBUG]:\e[0m";
            case eLogInfo:
                return "\e[1;32m[INFO]:\e[0m";
            default:
                return "[UNKNOWN]:";
        };

        return "[UNKNOWN]:";
    }

    // Overload redirect (<<) operator to be easier to use with code
    template<typename T>
    Logger &operator<< (T const &value)
    {
        data_buffer << value;
        return *this;
    }

private:
    // The output string stream as a buffer. There will be more added
    // to this as time goes on
    std::ostringstream data_buffer;
};

#endif

