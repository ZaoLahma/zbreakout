#include "breakout.h"
#include "engine.h"
#include "log.h"
#include "message_broker.h"
#include "sdl_renderer.h"
#include "sdl_window.h"

// Standard library
#include <iostream>

int main (int argc, char *argv[])
{
    zbreakout::core::log::Log log {std::cout};
    log.info(__func__, "zBrekaout starting...");

    zbreakout::core::message_broker::MessageBroker messageBroker {log};
    zbreakout::core::sdl_window::SDLWindow window {log, messageBroker};

    auto sdlWindow = window.createWindow("zBreakout", {800, 600});

    zbreakout::core::sdl_renderer::SDLRenderer renderer
    {
        log,
        sdlWindow
    };


    zbkreakout::game::breakout::Breakout breakout {log, messageBroker, renderer};

    zbreakout::core::engine::Engine engine {log, window, messageBroker, renderer, breakout};
    engine.start();

    /*
    while (true)
    {
        breakout.run();
        renderer.renderScene();
    }
    */

    return 0;
}