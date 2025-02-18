#pragma once

#include "breakout_block.h"
#include "log.h"
#include "renderer.h"
#include "window.h"

// Standard library
#include <memory>

namespace zbreakout::game::breakout_ball
{

class BreakoutBall
{
public:
    BreakoutBall(
        zbreakout::core::log::Log& log,
        std::shared_ptr<zbreakout::core::renderer::Renderer> renderer,
        const zbreakout::core::window::Resolution& resolution);
    ~BreakoutBall() = default;

    void render();

    void handlePaddleCollision();

    void resolveBlockCollision(core::renderer::ScreenPosition blockPosition, core::renderer::ScreenPosition blockSize);

    bool ballIsInPlay() const { return m_ballIsInPlay; }
    void resetBallIsInPlay() { m_ballIsInPlay = true; }

    zbreakout::core::renderer::ScreenPosition getPosition() const { return m_position; }
    zbreakout::core::renderer::ScreenPosition getAcceleration() const { return m_acceleration; }
    uint32_t getBallRadius() const { return m_ballRadius; }

private:
    void updatePosition();

    zbreakout::core::log::Log& m_log;
    std::shared_ptr<zbreakout::core::renderer::Renderer> m_renderer;
    const zbreakout::core::window::Resolution m_resolution;

    zbreakout::core::renderer::ScreenPosition m_position;
    zbreakout::core::renderer::ScreenPosition m_acceleration {0, 0};
    uint32_t m_ballRadius {10};
    bool m_ballIsInPlay {true};
};

}