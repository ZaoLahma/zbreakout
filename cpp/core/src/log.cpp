#include "log.h"

// Standard library
#include <iostream>

namespace zbreakout::core::log
{
Log::Log(std::ostream& stream) : m_stream(stream) {}
void Log::info(const std::string& context, const std::string& message)
{
    std::string prefix = context.empty() ? "" : "[" + context + "]";

    std::lock_guard<std::mutex> lock(m_logMutex);
    m_stream << prefix << " " << message << std::endl;
}

void Log::error(const std::string& context, const std::string& message)
{
    info("ERROR: " + context, message);
}
}