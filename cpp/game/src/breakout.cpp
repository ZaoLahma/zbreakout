#include "breakout.h"
#include "engine.h"
#include "user_input.h"
#include "window.h"

namespace zbreakout::game::breakout
{

Breakout::Breakout(
    zbreakout::core::log::Log& log,
    zbreakout::core::message_broker::MessageBroker& messageBroker,
    zbreakout::core::layered_renderer::LayeredRenderer& renderer,
    const zbreakout::core::window::Resolution& resolution) :
        zbreakout::core::engine::EngineApp(log, messageBroker),
        m_layeredRenderer(renderer), m_resolution(resolution)
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

    const zbreakout::core::renderer::ScreenPosition position {m_resolution.width / 2, m_resolution.height};
    m_breakoutPaddle = std::make_unique<zbreakout::game::breakout_paddle::BreakoutPaddle>(m_log, m_renderer, position);

    messageBroker.subscribeToMessageType(std::type_index(typeid(zbreakout::core::user_input::UserKeyInputMessage)), std::bind(&Breakout::processMessage, this, std::placeholders::_1));
}

void Breakout::processMessage(std::shared_ptr<zbreakout::core::message_broker::MessageBase> message)
{
    if (auto userKeyInputMessage = std::dynamic_pointer_cast<zbreakout::core::user_input::UserKeyInputMessage>(message))
    {
        if (userKeyInputMessage->type == zbreakout::core::user_input::UserKeyInputType::KeyPress)
        {
            switch (userKeyInputMessage->key)
            {
                case 'd':
                    m_breakoutPaddle->updatePosition({m_breakoutPaddle->getPosition().x + 1, m_breakoutPaddle->getPosition().y});
                    break;
                case 'a':
                    m_breakoutPaddle->updatePosition({m_breakoutPaddle->getPosition().x - 1, m_breakoutPaddle->getPosition().y});
                    break;
                default:
                    break;
            }
        }
    }
}

void Breakout::run()
{
    m_breakoutPaddle->render();
}

}