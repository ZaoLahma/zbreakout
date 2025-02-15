#include "breakout_ball.h"

namespace zbreakout::game::breakout_ball
{

BreakoutBall::BreakoutBall(
    zbreakout::core::log::Log& log,
    std::shared_ptr<zbreakout::core::renderer::Renderer> renderer,
    const zbreakout::core::window::Resolution& resolution) :
        m_log(log), m_renderer(renderer), m_resolution(resolution),
        m_position({resolution.width / 2, resolution.height / 2}), m_acceleration({5, 5}) {}

void BreakoutBall::render() 
{
    updatePosition();
    m_renderer->fillCircle(m_position, m_ballRadius, {255, 0, 0});
}

void BreakoutBall::handlePaddleCollision()
{
    if (m_acceleration.y > 0)
    {
        m_acceleration.y = -m_acceleration.y;
    }
}

void BreakoutBall::updatePosition()
{
    if (m_position.x + m_acceleration.x < 0)
    {
        m_position.x = 0;
        m_acceleration.x = -m_acceleration.x;
    }
    else if (m_position.x + m_acceleration.x > m_resolution.width)
    {
        m_position.x = m_resolution.width;
        m_acceleration.x = -m_acceleration.x;
    }

    if (m_position.y + m_acceleration.y < 0)
    {
        m_position.y = 0;
        m_acceleration.y = -m_acceleration.y;
    }
    else if (m_position.y + m_acceleration.y > m_resolution.height)
    {
        // Player lose condition - collision with floor
        m_acceleration.x = 0;
        m_acceleration.y = 0;
    }

    m_position.x += m_acceleration.x;
    m_position.y += m_acceleration.y;
}

}