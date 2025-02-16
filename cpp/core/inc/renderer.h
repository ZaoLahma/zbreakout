#pragma once

// Standard library
#include <cstdint>
#include <string>

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

    virtual void prepareRenderFrame() = 0;

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

    /**
     * Draw a filled circle
     *
     * @param position The center of the circle
     * @param radius The radius of the circle
     * @param color The color of the circle
     */
    virtual void fillCircle(const ScreenPosition& position, int radius, const Color& color) = 0;

    /**
     * Draw a filled rectangle
     *
     * @param position The top left corner of the rectangle
     * @param width The width of the rectangle
     * @param height The height of the rectangle
     * @param color The color of the rectangle
     */
    virtual void fillRectangle(const ScreenPosition& position, int width, int height, const Color& color) = 0;

    /**
     * Draw text
     *
     * @param text The text to draw
     * @param position The top left corner of the text
     * @param color The color of the text
     */
    virtual void renderText(const std::string& text, const ScreenPosition& position, const Color& color, const uint32_t scale = 1) = 0;
};

}