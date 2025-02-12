#include "breakout.h"
#include "engine.h"
#include "log.h"
#include "message_broker.h"
#include "window.h"

// Standard library
#include <iostream>

int main (int argc, char *argv[])
{
    zbreakout::core::log::Log log {std::cout};
    log.info(__func__, "Hello, world!");

    zbreakout::core::message_broker::MessageBroker messageBroker {log};
    zbreakout::core::window::Window window {log, messageBroker};

    zbreakout::core::engine::Engine engine {log, messageBroker};
    engine.start();

    window.createWindow("zBreakout", {800, 600});
    window.handleSDLEvents();

    return 0;
}