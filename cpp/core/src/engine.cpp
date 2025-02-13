#include "engine.h"

namespace zbreakout::core::engine
{
Engine::Engine(
    core::log::Log& log,
    core::message_broker::MessageBroker& messageBroker,
    core::renderer::Renderer& renderer, EngineApp& engineApp) :
        m_log(log), m_messageBroker(messageBroker),
        m_renderer(renderer), m_engineApp(engineApp),
        m_running(false)
{
    m_messageBroker.subscribeToMessageType(std::type_index(typeid(zbreakout::core::engine::GameQuitMessage)), std::bind(&Engine::processMessage, this, std::placeholders::_1));
}

Engine::~Engine()
{
    m_gameThread.join();
}

void Engine::start()
{
    m_gameThread = std::thread(&Engine::run, this);
}

void Engine::run()
{
    m_running = true;

    while (m_running)
    {
        m_messageBroker.processMessages();
        if (!m_running)
        {
            break;
        }
        m_renderer.drawCircle({100, 100}, 50, {255, 0, 0, 255});
        m_renderer.renderScene();
        //m_engineApp.run();
        //m_renderer.renderScene();
    }
}

void Engine::processMessage(std::shared_ptr<zbreakout::core::message_broker::MessageBase> message)
{
    m_running = false;
}

}