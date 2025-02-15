#include "breakout_paddle.h"
#include "window.h"

namespace zbreakout::game::breakout_paddle
{

BreakoutPaddle::BreakoutPaddle(
    zbreakout::core::log::Log& log,
    std::shared_ptr<zbreakout::core::renderer::Renderer> renderer,
    const zbreakout::core::window::Resolution& resolution) :
        m_log(log), m_renderer(renderer), m_resolution(resolution), m_position({resolution.width / 2 - PADDLE_WIDTH / 2, resolution.height - PADDLE_HEIGHT})
{
}

void BreakoutPaddle::handleInput(const PaddleDirection& direction)
{
    m_direction = direction;
}

void BreakoutPaddle::render()
{
    updatePosition();
    m_renderer->fillRectangle(m_position, PADDLE_WIDTH, PADDLE_HEIGHT, {255, 0, 0, 255});
}

void BreakoutPaddle::updatePosition()
{
    if (m_position.x < 0 || m_position.x > m_resolution.width - PADDLE_WIDTH)
    {
        m_acceleration.x = 0;

        if (m_position.x < 0)
        {
            m_position.x = 0;
        }
        else if (m_position.x > m_resolution.width - PADDLE_WIDTH)
        {
            m_position.x = m_resolution.width - PADDLE_WIDTH;
        }
    }

    switch (m_direction)
    {
        case PaddleDirection::LEFT:
                m_acceleration.x -= 1;
            break;
        case PaddleDirection::RIGHT:
                m_acceleration.x += 1;
            break;
        case PaddleDirection::NONE:
            if (m_acceleration.x > 0)
            {
                m_acceleration.x -= 1;
            }
            else if (m_acceleration.x < 0)
            {
                m_acceleration.x += 1;
            }
            break;
        default:
            break;
    }

    if (m_position.x + m_acceleration.x > 0 && m_position.x + m_acceleration.x < m_resolution.width - PADDLE_WIDTH)
    {
        m_position.x += m_acceleration.x;
    }
    else
    {
        if (m_position.x + m_acceleration.x < 0)
        {
            m_position.x = 0;
        }
        else if (m_position.x + m_acceleration.x > m_resolution.width - PADDLE_WIDTH)
        {
            m_position.x = m_resolution.width - PADDLE_WIDTH;
        }
        m_acceleration.x = 0;
    }
}

}