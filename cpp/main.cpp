#include "breakout.h"
#include "engine.h"
#include "log.h"
#include "message_broker.h"
#include "sdl_layered_renderer.h"
#include "sdl_window.h"

// Standard library
#include <iostream>

int main (int argc, char *argv[])
{
    zbreakout::core::log::Log log {std::cout};
    log.info(__func__, "zBrekaout starting...");

    zbreakout::core::message_broker::MessageBroker messageBroker {log};

    const zbreakout::core::window::Resolution resolution {610, 800};
    zbreakout::core::sdl_window::SDLWindow window {log, "zBreakout", resolution, messageBroker};

    zbreakout::core::sdl_layered_renderer::SDLLayeredRenderer layeredRenderer
    {
        log,
        window
    };


    zbreakout::game::breakout::Breakout breakout {log, messageBroker, layeredRenderer, resolution};

    zbreakout::core::engine::Engine engine {log, window, messageBroker, layeredRenderer, breakout};
    engine.start();

    return 0;
}