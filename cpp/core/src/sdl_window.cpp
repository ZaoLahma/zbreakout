#include "sdl_window.h"
#include "user_input.h"
#include "engine.h"

// SDL2
#include <SDL2/SDL.h>
#include <SDL_events.h>

namespace zbreakout::core::sdl_window
{

SDLWindow::SDLWindow(core::log::Log& log, core::message_broker::MessageBroker& messageBroker) : m_log(log), m_messageBroker(messageBroker)
{
    SDL_Init(SDL_INIT_VIDEO);

    m_log.info(__func__, "SDL initialized");
}

SDLWindow::~SDLWindow()
{
    SDL_Quit();

    m_log.info(__func__, "SDL quit");
}

SDL_Window* SDLWindow::createWindow(const std::string& title, const core::window::Resolution& resolution)
{
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolution.width, resolution.height, 0);

    if (m_window == nullptr)
    {
        m_log.error(__func__, "Failed to create window");
    }

    m_log.info(__func__, "Window created with title \"" + title + "\" and resolution " + std::to_string(resolution.width) + "x" + std::to_string(resolution.height));

    return m_window;
}

void SDLWindow::handleWindowEvents()
{
    handleSDLEvents();
}

void SDLWindow::handleSDLEvents()
{
    using UserKeyInputType = zbreakout::core::user_input::UserKeyInputType;
    using UserMouseInputType = zbreakout::core::user_input::UserMouseInputType;
    using UserMouseInputButton = zbreakout::core::user_input::UserMouseInputButton;
    using UserKeyInputMessage = zbreakout::core::user_input::UserKeyInputMessage;
    using UserMouseInputMessage = zbreakout::core::user_input::UserMouseInputMessage;
    
    using WindowClosedMessage = zbreakout::core::window::WindowClosedMessage;

    // Empty the SDL event queue
    SDL_Event event;
    while (1 == SDL_WaitEventTimeout(&event, 0))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                m_log.info(__func__, "Window close indication");
                m_messageBroker.sendMessage(std::make_shared<WindowClosedMessage>());
                break;
            case SDL_KEYDOWN:
                m_messageBroker.sendMessage(std::make_shared<UserKeyInputMessage>(UserKeyInputType::KeyPress, event.key.keysym.sym));
                break;
            case SDL_KEYUP:
                m_messageBroker.sendMessage(std::make_shared<UserKeyInputMessage>(UserKeyInputType::KeyRelease, event.key.keysym.sym));
                break;
            default:
                break;
        }
    }
}

}