#pragma once

#include "message_broker.h"

namespace zbreakout::core::user_input
{

enum class UserKeyInputType : uint8_t
{
    KeyPress,
    KeyRelease,
};

enum class UserMouseInputType : uint8_t
{
    MouseMove,
    MousePress,
    MouseRelease
};

enum class UserMouseInputButton : uint8_t
{
    Left,
    Right,
    Middle
};

class ScreenPosition
{
public:
    int x;
    int y;
};

class UserKeyInputMessage : public core::message_broker::MessageBase
{
public:
    UserKeyInputMessage(const UserKeyInputType& type, const unsigned char key) : type(type), key(key) {}
    UserKeyInputType type;
    unsigned char key;
};

class UserMouseInputMessage : public core::message_broker::MessageBase
{
public:
    UserMouseInputMessage(const UserMouseInputType& type, const ScreenPosition& position, UserMouseInputButton) : type(type), position(position), button(button) {}
    UserMouseInputType type;
    ScreenPosition position;
    UserMouseInputButton button;
};

}