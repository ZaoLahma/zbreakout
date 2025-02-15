#pragma once

#include "log.h"
#include "renderer.h"

// Standard library
#include <memory>


namespace zbreakout::game::breakout_block
{

class BreakoutBlock
{
public:
    BreakoutBlock(
        zbreakout::core::log::Log& log,
        std::shared_ptr<zbreakout::core::renderer::Renderer> renderer,
        const zbreakout::core::renderer::ScreenPosition& position,
        const zbreakout::core::renderer::ScreenPosition& blockSize) :
        m_log(log), m_renderer(renderer), m_position(position), m_blockSize(blockSize) {};

    void render();

    zbreakout::core::renderer::ScreenPosition getPosition() const { return m_position; }
    zbreakout::core::renderer::ScreenPosition getBlockSize() const { return m_blockSize; }

private:
    zbreakout::core::log::Log& m_log;
    std::shared_ptr<zbreakout::core::renderer::Renderer> m_renderer;
    zbreakout::core::renderer::ScreenPosition m_position;

    const zbreakout::core::renderer::ScreenPosition m_blockSize;
};

}