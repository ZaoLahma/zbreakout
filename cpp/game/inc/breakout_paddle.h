#pragma once

#include "log.h"
#include "renderer.h"
#include "window.h"

// Standard library
#include <cstdint>
#include <memory>

namespace zbreakout::game::breakout_paddle
{

constexpr uint8_t PADDLE_WIDTH {75};
constexpr uint8_t PADDLE_HEIGHT {10};

enum class PaddleDirection : uint8_t
{
    LEFT,
    RIGHT,
    NONE
};

class BreakoutPaddle
{
public:
    BreakoutPaddle(
        zbreakout::core::log::Log& log,
        std::shared_ptr<zbreakout::core::renderer::Renderer> renderer,
        const zbreakout::core::window::Resolution& resolution);
    ~BreakoutPaddle() = default;

    zbreakout::core::renderer::ScreenPosition getPosition() const { return m_position; }
    zbreakout::core::renderer::ScreenPosition getPaddleSize() const { return {PADDLE_WIDTH, PADDLE_HEIGHT}; }

    void handleInput(const PaddleDirection& direction);

    void render();
private:
    void updatePosition();

    zbreakout::core::log::Log& m_log;
    std::shared_ptr<zbreakout::core::renderer::Renderer> m_renderer;
    const zbreakout::core::window::Resolution m_resolution;

    zbreakout::core::renderer::ScreenPosition m_position;
    PaddleDirection m_direction {PaddleDirection::NONE};
    zbreakout::core::renderer::ScreenPosition m_acceleration {0, 0};
};

}