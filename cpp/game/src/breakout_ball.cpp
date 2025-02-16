#include "breakout_ball.h"
#include <random>

namespace zbreakout::game::breakout_ball
{

BreakoutBall::BreakoutBall(
    zbreakout::core::log::Log& log,
    std::shared_ptr<zbreakout::core::renderer::Renderer> renderer,
    const zbreakout::core::window::Resolution& resolution) :
        m_log(log), m_renderer(renderer), m_resolution(resolution),
        m_position({resolution.width / 2, resolution.height / 2}) 
{
    // Randomize start position within the lower third of the screen
    m_position.x = rand() % (resolution.width / 3) + resolution.width / 3;
    m_position.y = rand() % (resolution.height / 3) + resolution.height / 3;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);

    m_acceleration.x = (distrib(gen) == 0) ? -5 : 5;
    m_acceleration.y = 5;
}

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

void BreakoutBall::resolveBlockCollision(core::renderer::ScreenPosition blockPosition, core::renderer::ScreenPosition blockSize)
{
    float overlapLeft   = (m_position.x + m_ballRadius) - blockPosition.x;
    float overlapRight  = (blockPosition.x + blockSize.x) - (m_position.x - m_ballRadius);
    float overlapTop    = (m_position.y + m_ballRadius) - blockPosition.y;
    float overlapBottom = (blockPosition.y + blockSize.y) - (m_position.y - m_ballRadius);

    float minOverlapX = std::min(overlapLeft, overlapRight);
    float minOverlapY = std::min(overlapTop, overlapBottom);

    if (minOverlapX < minOverlapY)
    {
        // Ball hit left or right
        m_acceleration.x = -m_acceleration.x;
    }
    else
    {
        // Ball hit top or bottom
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