#include "window.h"
#include "user_input.h"
#include "engine.h"

// SDL2
#include <SDL2/SDL.h>

namespace zbreakout::core::window
{

Window::Window(core::log::Log& log, core::message_broker::MessageBroker& messageBroker) : m_log(log), m_messageBroker(messageBroker)
{
    SDL_Init(SDL_INIT_VIDEO);
}

void Window::createWindow(const std::string& title, const resolution& resolution)
{
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolution.width, resolution.height, 0);

    if (m_window == nullptr)
    {
        m_log.error(__func__, "Failed to create window");
        return;
    }

    m_log.info(__func__, "Window created with title \"" + title + "\" and resolution " + std::to_string(resolution.width) + "x" + std::to_string(resolution.height));
}

void Window::handleSDLEvents()
{
    m_log.info(__func__, "Window event loop started");
    using UserKeyInputType = zbreakout::core::user_input::UserKeyInputType;
    using UserMouseInputType = zbreakout::core::user_input::UserMouseInputType;
    using UserMouseInputButton = zbreakout::core::user_input::UserMouseInputButton;
    using UserKeyInputMessage = zbreakout::core::user_input::UserKeyInputMessage;
    using UserMouseInputMessage = zbreakout::core::user_input::UserMouseInputMessage;
    
    using GameQuitMessage = zbreakout::core::engine::GameQuitMessage;

    bool continueRunning {true};
    while (continueRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                case SDL_WINDOWEVENT_CLOSE:
                    SDL_Quit();
                    m_log.info(__func__, "Window closed");
                    m_messageBroker.sendMessage(std::make_shared<GameQuitMessage>());
                    continueRunning = false;
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

            if (!continueRunning)
            {
                break;
            }
        }

        if (!continueRunning)
        {
            break;
        }
    }
}

}