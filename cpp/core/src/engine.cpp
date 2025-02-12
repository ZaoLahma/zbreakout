#include "engine.h"

namespace zbreakout::core::engine
{
Engine::Engine(core::log::Log& log, core::message_broker::MessageBroker& messageBroker) : m_log(log), m_messageBroker(messageBroker), m_running(false)
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
    }
}

void Engine::processMessage(std::shared_ptr<zbreakout::core::message_broker::MessageBase> message)
{
    m_log.info(__func__, "Processing message " + std::string(typeid(*message).name()));
    if (std::type_index(typeid(*message)) == std::type_index(typeid(zbreakout::core::engine::GameQuitMessage)))
    {
        m_running = false;
        m_log.info(__func__, "Game quit message handled");
    }
}

}