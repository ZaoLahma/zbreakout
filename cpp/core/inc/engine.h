#pragma once

#include "message_broker.h"
#include "log.h"

// Standard library
#include <thread>

namespace zbreakout::core::engine
{

class GameQuitMessage : public zbreakout::core::message_broker::MessageBase
{
public:
    GameQuitMessage() = default;
};

class Engine
{
public:
    Engine() = delete;
    Engine(zbreakout::core::log::Log& log, zbreakout::core::message_broker::MessageBroker& messageBroker);
    ~Engine();

    void start();

private:
    void run();
    void processMessage(std::shared_ptr<zbreakout::core::message_broker::MessageBase> message);

    zbreakout::core::log::Log& m_log;
    zbreakout::core::message_broker::MessageBroker& m_messageBroker;
    bool m_running;

    // Game thread
    std::thread m_gameThread;
};

}