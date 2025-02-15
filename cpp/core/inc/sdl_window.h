#pragma once

#include "log.h"
#include "message_broker.h"
#include "window.h"

// Standard library
#include <string>

struct SDL_Window;

namespace zbreakout::core::sdl_window
{

class SDLWindow : public core::window::Window
{
public:
    SDLWindow() = delete;
    SDLWindow(core::log::Log& log, core::message_broker::MessageBroker& messageBroker);
    ~SDLWindow();

    SDL_Window* createWindow(const std::string& title, const core::window::Resolution& resolution);

    void handleWindowEvents() override;

private:
    /**
     * Handle SDL events - Must be executed in the main thread
     */
     void handleSDLEvents();

    core::log::Log& m_log;
    SDL_Window* m_window;
    core::message_broker::MessageBroker& m_messageBroker;
};

}