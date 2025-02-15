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
    virtual void handleWindowEvents() = 0;
};

}