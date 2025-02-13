#pragma once

#include "log.h"
#include "message_broker.h"

// Standard library
#include <string>

struct SDL_Window;

namespace zbreakout::core::window
{

struct resolution
{
    int width;
    int height;
};

class Window
{
public:
    Window() = delete;
    Window(core::log::Log& log, core::message_broker::MessageBroker& messageBroker);

    SDL_Window* createWindow(const std::string& title, const resolution& resolution);

    /**
     * Handle SDL events - Must be executed in the main thread
     */
    void handleSDLEvents();

private:
    core::log::Log& m_log;
    SDL_Window* m_window;
    core::message_broker::MessageBroker& m_messageBroker;
};

}