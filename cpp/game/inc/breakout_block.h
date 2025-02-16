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

    void handleBallCollision();

    zbreakout::core::renderer::ScreenPosition getPosition() const { return m_position; }
    zbreakout::core::renderer::ScreenPosition getBlockSize() const { return m_blockSize; }
    uint8_t getBlockHealth() const { return m_blockHealth; }
    void setBlockHealth(uint8_t health) { m_blockHealth = health; }

private:
    zbreakout::core::log::Log& m_log;
    std::shared_ptr<zbreakout::core::renderer::Renderer> m_renderer;
    zbreakout::core::renderer::ScreenPosition m_position;

    const zbreakout::core::renderer::ScreenPosition m_blockSize;

    uint8_t m_blockHealth {1};
};

}