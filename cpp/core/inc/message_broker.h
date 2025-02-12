#pragma once

#include "log.h"

// Standard library
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <typeindex>
#include <queue>


namespace zbreakout::core::message_broker
{

class MessageBase
{
public:
    virtual ~MessageBase() = default;
};

class MessageBroker
{
public:
    MessageBroker() = delete;
    MessageBroker(core::log::Log& log ) : m_log(log) {}
    virtual ~MessageBroker() = default;

    void subscribeToMessageType(const std::type_index& type, std::function<void(std::shared_ptr<MessageBase>)> callback);

    void sendMessage(std::shared_ptr<MessageBase> message);

    void processMessages();

private:
    core::log::Log& m_log;
    std::queue<std::shared_ptr<MessageBase>> m_messageQueue;
    std::map<std::type_index, std::vector<std::function<void(std::shared_ptr<MessageBase>)>>> m_subscribers;
    std::mutex m_messageMutex;
};
}