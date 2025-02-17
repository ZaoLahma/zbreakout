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
    constexpr double FIXED_TIMESTEP {1.0 / TARGET_FPS}; // 60 updates per second (in seconds)
    
    uint64_t frameCounter {0};
    double accumulator {0.0};
    
    auto previousTime = std::chrono::high_resolution_clock::now();
    
    while (m_running)
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        
        double deltaTime = elapsedTime.count();
        
        accumulator += deltaTime;
    
        m_window.handleWindowEvents();
        m_messageBroker.processMessages();

        if (!m_running)
        {
            break;
        }

        while (accumulator >= FIXED_TIMESTEP)
        {
            m_renderer.prepareRenderFrame();
            m_engineApp.run(FIXED_TIMESTEP);
            m_renderer.finalizeRenderFrame();
            accumulator -= FIXED_TIMESTEP;
        }
    
        m_renderer.renderFrame();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    
        frameCounter++;
        if (frameCounter % TARGET_FPS == 0)
        {
            m_log.info(__func__, "FPS: " + std::to_string(frameCounter));
            frameCounter = 0;
        }
    }
}

void Engine::processMessage(std::shared_ptr<zbreakout::core::message_broker::MessageBase> message)
{
    m_running = false;
}

}