#pragma once

#include "breakout_paddle.h"
#include "engine.h"
#include "layered_renderer.h"
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
        zbreakout::core::layered_renderer::LayeredRenderer& renderer,
        const zbreakout::core::window::Resolution& resolution);
    ~Breakout() = default;

    void run();

private:
    void processMessage(std::shared_ptr<zbreakout::core::message_broker::MessageBase> message);

    zbreakout::core::layered_renderer::LayeredRenderer& m_layeredRenderer;
    std::shared_ptr<zbreakout::core::renderer::Renderer> m_renderer;
    zbreakout::core::window::Resolution m_resolution;

    std::unique_ptr<zbreakout::game::breakout_paddle::BreakoutPaddle> m_breakoutPaddle;
};

}