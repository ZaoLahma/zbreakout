#include "breakout.h"
#include "breakout_paddle.h"
#include "engine.h"
#include "user_input.h"
#include "window.h"

// Standard library
#include <algorithm>

namespace zbreakout::game::breakout
{

Breakout::Breakout(
    zbreakout::core::log::Log& log,
    zbreakout::core::message_broker::MessageBroker& messageBroker,
    zbreakout::core::layered_renderer::LayeredRenderer& renderer,
    const zbreakout::core::window::Resolution& resolution) :
        zbreakout::core::engine::EngineApp(log, messageBroker),
        m_layeredRenderer(renderer), m_resolution(resolution)
{
    m_layeredRenderer.addLayer(0);

    if (auto renderer = m_layeredRenderer.getRendererForLayer(0); renderer.has_value())
    {
        m_renderer = renderer.value();
    }
    else
    {
        m_log.error(__func__, "Failed to get renderer for layer 0");
    }

    m_breakoutBall = std::make_unique<zbreakout::game::breakout_ball::BreakoutBall>(m_log, m_renderer, resolution);
    const zbreakout::core::renderer::ScreenPosition position {m_resolution.width / 2, m_resolution.height};
    m_breakoutPaddle = std::make_unique<zbreakout::game::breakout_paddle::BreakoutPaddle>(m_log, m_renderer, resolution);

    const int numBlockColumns {7};
    const int blockSpacing {3};

    const int totalSpacing = (numBlockColumns - 1) * blockSpacing;
    const int blockWidth = (m_resolution.width - totalSpacing) / numBlockColumns;
    const uint32_t numBlockRows {5};
    const int blockHeight {blockWidth / 2};

    const int totalBlockWidth = numBlockColumns * blockWidth + totalSpacing;
    const int startX = (m_resolution.width - totalBlockWidth) / 2;  // Centering the blocks

    for (int column {0}; column < numBlockColumns; ++column)
    {
        for (int row {0}; row < numBlockRows; ++row)
        {
            const int x {startX + column * (blockWidth + blockSpacing)};  // Centered positioning
            const int y {blockSpacing + row * (blockHeight + blockSpacing)};
            const zbreakout::core::renderer::ScreenPosition position {x, y};
            const zbreakout::core::renderer::ScreenPosition size {blockWidth, blockHeight};
            m_breakoutBlocks.push_back(std::make_shared<zbreakout::game::breakout_block::BreakoutBlock>(m_log, m_renderer, position, size));

            // Set initial block health
            if (row < 2)
            {
                m_breakoutBlocks.back()->setBlockHealth(1);
            }
            else if (row < 4)
            {
                m_breakoutBlocks.back()->setBlockHealth(2);
            }
            else
            {
                m_breakoutBlocks.back()->setBlockHealth(3);
            }
        }
    }

    messageBroker.subscribeToMessageType(
        std::type_index(
            typeid(zbreakout::core::user_input::UserKeyInputMessage)),
            std::bind(&Breakout::processMessage, this, std::placeholders::_1));
}

void Breakout::processMessage(std::shared_ptr<zbreakout::core::message_broker::MessageBase> message)
{
    using InputDirection = zbreakout::game::breakout_paddle::PaddleDirection;
    if (auto userKeyInputMessage = std::dynamic_pointer_cast<zbreakout::core::user_input::UserKeyInputMessage>(message))
    {
        if (userKeyInputMessage->type == zbreakout::core::user_input::UserKeyInputType::KeyPress)
        {
            switch (userKeyInputMessage->key)
            {
                case 'd':
                    m_breakoutPaddle->handleInput(InputDirection::RIGHT);
                    break;
                case 'a':
                    m_breakoutPaddle->handleInput(InputDirection::LEFT);
                    break;
                default:
                    break;
            }
        }
        else if (userKeyInputMessage->type == zbreakout::core::user_input::UserKeyInputType::KeyRelease)
        {
            m_breakoutPaddle->handleInput(InputDirection::NONE);
        }
    }
}

bool Breakout::checkBallCollision(
    const zbreakout::core::renderer::ScreenPosition& objectPosition,
    const zbreakout::core::renderer::ScreenPosition& objectSize,
    const zbreakout::core::renderer::ScreenPosition& ballPosition,
    const zbreakout::core::renderer::ScreenPosition &ballAcceleration,
    uint32_t ballRadius)
{
        float blockLeft = objectPosition.x;
        float blockRight = objectPosition.x + objectSize.x;
        float blockTop = objectPosition.y;
        float blockBottom = objectPosition.y + objectSize.y;
    
        float closestX = std::max(blockLeft, std::min((float) ballPosition.x, blockRight));
        float closestY = std::max(blockTop, std::min((float) ballPosition.y, blockBottom));
    
        float dx = ballPosition.x - closestX;
        float dy = ballPosition.y - closestY;
        float distanceSquared = (dx * dx) + (dy * dy);
    
        return distanceSquared <= (ballRadius * ballRadius);
}

void Breakout::run()
{
    m_breakoutBall->render();
    m_breakoutPaddle->render();

    for (const auto& block : m_breakoutBlocks)
    {
        block->render();
    }

    if (checkBallCollision(
        m_breakoutPaddle->getPosition(),
        m_breakoutPaddle->getPaddleSize(),
        m_breakoutBall->getPosition(),
        m_breakoutBall->getAcceleration(),
        m_breakoutBall->getBallRadius()))
    {
        m_breakoutBall->handlePaddleCollision();
    }

    std::vector<std::shared_ptr<zbreakout::game::breakout_block::BreakoutBlock>> blocksToRemove;
    for (const auto& block : m_breakoutBlocks)
    {
        if (checkBallCollision(
            block->getPosition(),
            block->getBlockSize(),
            m_breakoutBall->getPosition(),
            m_breakoutBall->getAcceleration(),
            m_breakoutBall->getBallRadius()))
        {
            block->handleBallCollision();
            m_breakoutBall->resolveBlockCollision(block->getPosition(), block->getBlockSize());

            if (block->getBlockHealth() == 0)
            {
                blocksToRemove.push_back(block);
            }
        }
    }

    for (const auto& block : blocksToRemove)
    {
        m_breakoutBlocks.erase(std::remove(m_breakoutBlocks.begin(), m_breakoutBlocks.end(), block), m_breakoutBlocks.end());
    }
}

}