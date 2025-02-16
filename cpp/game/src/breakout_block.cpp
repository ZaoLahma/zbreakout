#include "breakout_block.h"
#include "renderer.h"
#include <map>

// Standard library

namespace zbreakout::game::breakout_block
{

constexpr core::renderer::Color RED {255, 0, 0, 255};
constexpr core::renderer::Color GREEN {0, 255, 0, 255};
constexpr core::renderer::Color YELLOW {255, 255, 0, 255};

// Health to color mapping
const std::map<uint8_t, core::renderer::Color> healthToColor
{
    {1, GREEN},
    {2, YELLOW},
    {3, RED}
};

void BreakoutBlock::render()
{
    if (m_blockHealth != 0)
    {
        m_renderer->fillRectangle(m_position, m_blockSize.x, m_blockSize.y, healthToColor.at(m_blockHealth));
    }
}

void BreakoutBlock::handleBallCollision()
{
    --m_blockHealth;
}

}