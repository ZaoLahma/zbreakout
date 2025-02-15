#include "breakout_block.h"

// Standard library

namespace zbreakout::game::breakout_block
{

void BreakoutBlock::render()
{
    m_renderer->fillRectangle(m_position, m_blockSize.x, m_blockSize.y, {255, 0, 0, 255});
}

}