#pragma once

#include "breakout_ball.h"
#include "breakout_block.h"
#include "breakout_paddle.h"
#include "breakout_ui.h"
#include "engine.h"
#include "frame_renderer.h"
#include "renderer.h"
#include "window.h"

// Standard library
#include <memory>

namespace zbreakout::game::breakout
{

class Breakout : public zbreakout::core::engine::EngineApp
{
public:
    Breakout(
        zbreakout::core::log::Log& log,
        zbreakout::core::message_broker::MessageBroker& messageBroker,
        zbreakout::core::layered_renderer::LayeredFrameRenderer& renderer,
        const zbreakout::core::window::Resolution& resolution);
    ~Breakout() = default;

    virtual void run(const double timeStep) override;

private:
    void processMessage(std::shared_ptr<zbreakout::core::message_broker::MessageBase> message);

    bool checkBallCollision(
        const zbreakout::core::renderer::ScreenPosition& objectPosition,
        const zbreakout::core::renderer::ScreenPosition& objectSize,
        const zbreakout::core::renderer::ScreenPosition& ballPosition,
        const zbreakout::core::renderer::ScreenPosition &ballAcceleration,
        uint32_t ballRadius);

    zbreakout::core::layered_renderer::LayeredFrameRenderer& m_layeredRenderer;
    std::shared_ptr<zbreakout::core::renderer::Renderer> m_fieldRenderer;
    std::shared_ptr<zbreakout::core::renderer::Renderer> m_uiRenderer;

    zbreakout::core::window::Resolution m_resolution;

    std::unique_ptr<zbreakout::game::breakout_ball::BreakoutBall> m_breakoutBall;
    std::unique_ptr<zbreakout::game::breakout_paddle::BreakoutPaddle> m_breakoutPaddle;

    std::vector<std::shared_ptr<zbreakout::game::breakout_block::BreakoutBlock>> m_breakoutBlocks;

    std::unique_ptr<zbreakout::game::breakout_ui::BreakoutUI> m_breakoutUI;
};

}