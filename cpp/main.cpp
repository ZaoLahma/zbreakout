#include "breakout.h"
#include "engine.h"
#include "log.h"
#include "message_broker.h"
#include "sdl_renderer.h"
#include "window.h"

// Standard library
#include <iostream>

// SDL2
#include <SDL_render.h>
#include <SDL_error.h>

int main (int argc, char *argv[])
{
    zbreakout::core::log::Log log {std::cout};
    log.info(__func__, "Hello, world!");

    zbreakout::core::message_broker::MessageBroker messageBroker {log};
    zbreakout::core::window::Window window {log, messageBroker};

    auto sdlWindow = window.createWindow("zBreakout", {800, 600});


    /*
    zbreakout::core::sdl_renderer::SDLRenderer renderer
    {
        log,
        sdlWindow
    };
    */

    auto renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect {100, 100, 200, 100};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    //zbkreakout::game::breakout::Breakout breakout {log, messageBroker, renderer};

    //zbreakout::core::engine::Engine engine {log, messageBroker, renderer, breakout};
    //engine.start();

    window.handleSDLEvents();

    return 0;
}