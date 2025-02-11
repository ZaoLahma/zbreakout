#include "breakout.h"
#include "engine.h"
#include "log.h"

// Standard library
#include <iostream>

int main (int argc, char *argv[])
{
    zbreakout::core::log::Log log {std::cout};
    log.info(__func__, "Hello, world!");

    return 0;
}