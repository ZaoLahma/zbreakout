#pragma once

#include "engine.h"
#include "renderer.h"

namespace zbkreakout::game::breakout
{

class Breakout : public zbreakout::core::engine::EngineApp
{
public:
    Breakout(zbreakout::core::log::Log& log, zbreakout::core::message_broker::MessageBroker& messageBroker, zbreakout::core::renderer::Renderer& renderer);
    ~Breakout() = default;

    void run();

private:

};

}