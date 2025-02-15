#include "breakout.h"
#include "engine.h"

namespace zbkreakout::game::breakout
{

Breakout::Breakout(
    zbreakout::core::log::Log& log,
    zbreakout::core::message_broker::MessageBroker& messageBroker,
    zbreakout::core::layered_renderer::LayeredRenderer& renderer) : zbreakout::core::engine::EngineApp(log, messageBroker), m_layeredRenderer(renderer)
{
    m_layeredRenderer.addLayer(0);

    if (auto renderer = m_layeredRenderer.getRendererForLayer(0); renderer.has_value())
    {
        m_renderer = renderer.value();
    }
    else
    {
        m_log.error(__func__, "Failed to get renderer for layer 0");
    }
}

void Breakout::run()
{
    m_renderer->fillRectangle({100, 100}, 50, 50, {255, 0, 0, 255});
    m_renderer->fillRectangle({200, 200}, 50, 50, {0, 255, 0, 255});
    m_renderer->fillRectangle({300, 300}, 50, 50, {0, 0, 255, 255});
}

}