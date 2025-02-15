#pragma once

#include "message_broker.h"
#include "log.h"
#include "renderer.h"
#include "window.h"

namespace zbreakout::core::engine
{

class EngineApp
{
public:
    EngineApp() = delete;
    EngineApp(
        zbreakout::core::log::Log& log,
        zbreakout::core::message_broker::MessageBroker& messageBroker,
        zbreakout::core::renderer::Renderer& renderer) : m_log(log), m_messageBroker(messageBroker), m_renderer(renderer) {}

    ~EngineApp() = default;
    
    virtual void run() = 0;
protected:
    zbreakout::core::log::Log& m_log;
    zbreakout::core::message_broker::MessageBroker& m_messageBroker;
    zbreakout::core::renderer::Renderer& m_renderer;
};

class Engine
{
public:
    Engine() = delete;
    Engine(
        zbreakout::core::log::Log& log,
        zbreakout::core::window::Window& window,
        zbreakout::core::message_broker::MessageBroker& messageBroker,
        zbreakout::core::renderer::Renderer& renderer,
        EngineApp& engineApp);
    ~Engine();

    void start();

private:
    void run();
    void processMessage(std::shared_ptr<zbreakout::core::message_broker::MessageBase> message);

    zbreakout::core::log::Log& m_log;
    zbreakout::core::window::Window& m_window;
    zbreakout::core::message_broker::MessageBroker& m_messageBroker;
    zbreakout::core::renderer::Renderer& m_renderer;
    EngineApp& m_engineApp;

    bool m_running;
};

}