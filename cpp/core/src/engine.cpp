#include "engine.h"

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

    while (m_running)
    {
        m_window.handleWindowEvents();
        m_messageBroker.processMessages();

        if (!m_running)
        {
            break;
        }

        m_engineApp.run();
        m_renderer.renderFrame();
    }
}

void Engine::processMessage(std::shared_ptr<zbreakout::core::message_broker::MessageBase> message)
{
    m_running = false;
}

}