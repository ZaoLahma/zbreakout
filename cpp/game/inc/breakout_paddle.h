#pragma once

#include "log.h"
#include "renderer.h"

// Standard library
#include <memory>

namespace zbreakout::game::breakout_paddle
{

class BreakoutPaddle
{
public:
    BreakoutPaddle(
        zbreakout::core::log::Log& log,
        std::shared_ptr<zbreakout::core::renderer::Renderer> renderer,
        const zbreakout::core::renderer::ScreenPosition& position);
    ~BreakoutPaddle() = default;

    zbreakout::core::renderer::ScreenPosition getPosition() const { return m_position; }

    void updatePosition(const zbreakout::core::renderer::ScreenPosition& position);

    void render();
private:
    zbreakout::core::log::Log& m_log;
    std::shared_ptr<zbreakout::core::renderer::Renderer> m_renderer;

    zbreakout::core::renderer::ScreenPosition m_position;
};

}