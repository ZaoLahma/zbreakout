#pragma once

#include "message_broker.h"

namespace zbreakout::core::window
{

struct Resolution
{
    int width;
    int height;
};

class WindowClosedMessage : public zbreakout::core::message_broker::MessageBase
{
public:
    WindowClosedMessage() = default;
};

class Window
{
public:
    Window() = delete;
    Window(const Resolution& resolution) : m_windowResolution(resolution) {}

    virtual void handleWindowEvents() = 0;

    Resolution getWindowResolution() const { return m_windowResolution; }

private:
    Resolution m_windowResolution;
};

}