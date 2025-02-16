#pragma once

// Standard library
#include "log.h"
#include "renderer.h"
#include "window.h"
#include <cstdint>
#include <memory>
#include <string>

namespace zbreakout::game::breakout_ui
{

class BreakoutUI
{
public:
    BreakoutUI(
        zbreakout::core::log::Log& log,
        std::shared_ptr<zbreakout::core::renderer::Renderer> renderer,
        const zbreakout::core::window::Resolution& resolution) : m_log(log), m_renderer(renderer), m_resolution(resolution), m_scoreText("Score ") {}
    virtual ~BreakoutUI() = default;

    void render();

    void addToScore(uint32_t score) { m_score += score; }

    void resetScore() { m_score = 0; }

private:
    zbreakout::core::log::Log& m_log;
    std::shared_ptr<zbreakout::core::renderer::Renderer> m_renderer;
    const zbreakout::core::window::Resolution m_resolution;

    uint32_t m_score {0};
    std::string m_scoreText;

};

}