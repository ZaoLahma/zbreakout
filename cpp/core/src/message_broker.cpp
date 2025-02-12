#include "message_broker.h"

namespace zbreakout::core::message_broker
{


void MessageBroker::subscribeToMessageType(const std::type_index& type, std::function<void(std::shared_ptr<MessageBase>)> callback)
{
    std::lock_guard<std::mutex> lock(m_messageMutex);
    const auto& it = m_subscribers.find(type);
    if (it == m_subscribers.end())
    {
        m_subscribers.emplace(type, std::vector<std::function<void(std::shared_ptr<MessageBase>)>>());
    }

    m_subscribers[type].emplace_back(callback);
}

void MessageBroker::sendMessage(std::shared_ptr<MessageBase> message)
{
    std::lock_guard<std::mutex> lock(m_messageMutex);
    m_messageQueue.push(message);
}

void MessageBroker::processMessages()
{
    std::lock_guard<std::mutex> lock(m_messageMutex);
    while (!m_messageQueue.empty())
    {
        auto message = m_messageQueue.front();
        m_messageQueue.pop();
        const auto& it = m_subscribers.find(std::type_index(typeid(*message)));
        if (it != m_subscribers.end())
        {
            for (const auto& callback : it->second)
            {
                callback(message);
            }
        }
    }
}

}