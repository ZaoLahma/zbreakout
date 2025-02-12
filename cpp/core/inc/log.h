#pragma once

// Standard library
#include <mutex>
#include <string>

namespace zbreakout::core::log
{

class Log
{
public:
    Log() = delete;
    Log(std::ostream& stream);

    void info(const std::string& context, const std::string& message);
    void error(const std::string& context, const std::string& message);

private:
    std::ostream& m_stream;
    std::mutex m_logMutex;
};

}