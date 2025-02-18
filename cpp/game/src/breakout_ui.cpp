#include "breakout_ui.h"

namespace zbreakout::game::breakout_ui
{

void BreakoutUI::render()
{
    m_renderer->renderText(m_scoreText + std::to_string(m_score), {5, 5}, {255, 255, 255}, 3);
}

}