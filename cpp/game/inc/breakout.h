#pragma once

#include "engine.h"
#include "layered_renderer.h"
#include "renderer.h"

namespace zbkreakout::game::breakout
{

class Breakout : public zbreakout::core::engine::EngineApp
{
public:
    Breakout(zbreakout::core::log::Log& log, zbreakout::core::message_broker::MessageBroker& messageBroker, zbreakout::core::layered_renderer::LayeredRenderer& renderer);
    ~Breakout() = default;

    void run();

private:
    zbreakout::core::layered_renderer::LayeredRenderer& m_layeredRenderer;
    std::shared_ptr<zbreakout::core::renderer::Renderer> m_renderer;

};

}