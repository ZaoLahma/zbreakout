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

class Renderer
{
public:
    Renderer() = default;
    virtual ~Renderer() = default;

    virtual void drawCircle(const ScreenPosition& position, int radius, const Color& color) = 0;
    virtual void drawRectangle(const ScreenPosition& position, int width, int height, const Color& color) = 0;

    /**
     * Call once per frame to render the scene
     */
    virtual void renderScene() = 0;
};

}