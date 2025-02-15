#include "engine.h"
#include <cstdint>
#include <thread>

namespace zbreakout::core::engine
{
Engine::Engine(
    core::log::Log& log,
    core::window::Window& window,
    core::message_broker::MessageBroker& messageBroker,
    core::renderer::FrameRenderer& renderer, EngineApp& engineApp) :
        m_log(log), m_window(window),
        m_messageBroker(messageBroker), m_renderer(renderer),
        m_engineApp(engineApp), m_running(false)
{
    m_messageBroker.subscribeToMessageType(std::type_index(typeid(zbreakout::core::window::WindowClosedMessage)), std::bind(&Engine::processMessage, this, std::placeholders::_1));
}

Engine::~Engine()
{
}

void Engine::start()
{
    run();
}

void Engine::run()
{
    m_running = true;

    constexpr uint64_t TARGET_FPS {60};
    uint64_t frameCounter {0};
    while (m_running)
    {
        const auto startTime = std::chrono::high_resolution_clock::now();

        m_window.handleWindowEvents();
        m_messageBroker.processMessages();

        if (!m_running)
        {
            break;
        }

        m_engineApp.run();
        m_renderer.renderFrame();

        const auto endTime = std::chrono::high_resolution_clock::now();
        const auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        const auto sleepTime = 1000 / TARGET_FPS - timeDiff;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

        frameCounter++;
        if (frameCounter % TARGET_FPS == 0)
        {
            const auto fps {frameCounter};
            m_log.info(__func__, "FPS: " + std::to_string(fps));
            frameCounter = 0;
        }
    }
}

void Engine::processMessage(std::shared_ptr<zbreakout::core::message_broker::MessageBase> message)
{
    m_running = false;
}

}