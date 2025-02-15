#include "breakout_paddle.h"

namespace zbreakout::game::breakout_paddle
{

BreakoutPaddle::BreakoutPaddle(
    zbreakout::core::log::Log& log,
    std::shared_ptr<zbreakout::core::renderer::Renderer> renderer,
    const zbreakout::core::renderer::ScreenPosition& position) : m_log(log), m_renderer(renderer), m_position({position.x, position.y - 30})
{
}

void BreakoutPaddle::updatePosition(const zbreakout::core::renderer::ScreenPosition& position)
{
    m_position = position;
}

void BreakoutPaddle::render()
{
    m_renderer->fillRectangle(m_position, 50, 50, {255, 0, 0, 255});
}

}