#pragma once

namespace zbreakout::core::renderer
{

struct ScreenPosition
{
    int x;
    int y;
};

struct Color
{
    int r;
    int g;
    int b;
    int a {255};
};

class FrameRenderer
{
public:
    FrameRenderer() = default;
    virtual ~FrameRenderer() = default;

    /**
     * Call once per frame to render the frame
     */
     virtual void renderFrame() = 0;
};

class Renderer : public FrameRenderer
{
public:
    Renderer() = default;
    virtual ~Renderer() = default;

    virtual void fillCircle(const ScreenPosition& position, int radius, const Color& color) = 0;
    virtual void fillRectangle(const ScreenPosition& position, int width, int height, const Color& color) = 0;
};

}