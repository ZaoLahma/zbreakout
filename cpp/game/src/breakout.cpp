#include "breakout.h"
#include "engine.h"

namespace zbkreakout::game::breakout
{

Breakout::Breakout(
    zbreakout::core::log::Log& log,
    zbreakout::core::message_broker::MessageBroker& messageBroker,
    zbreakout::core::renderer::Renderer& renderer) : zbreakout::core::engine::EngineApp(log, messageBroker, renderer)
{
    
}

void Breakout::run()
{
    m_renderer.drawRectangle({100, 100}, 50, 50, {255, 0, 0, 255});
    m_renderer.drawRectangle({200, 200}, 50, 50, {0, 255, 0, 255});
    m_renderer.drawRectangle({300, 300}, 50, 50, {0, 0, 255, 255});

    m_log.info(__func__, "Running game");
}

}