#pragma once

#include "log.h"
#include "renderer.h"
#include "sdl_window.h"

struct SDL_Renderer;
struct SDL_Texture;

namespace zbreakout::core::sdl_renderer
{

class SDLRenderer : public zbreakout::core::renderer::Renderer
{
public:
    SDLRenderer(zbreakout::core::log::Log& log, zbreakout::core::sdl_window::SDLWindow& window);
    ~SDLRenderer();
    void fillCircle(const core::renderer::ScreenPosition& position, int radius, const core::renderer::Color& color) override;
    void fillRectangle(const core::renderer::ScreenPosition& position, int width, int height, const core::renderer::Color& color) override;

    void renderFrame() override;

private:
    static void initializeSDLRenderer(zbreakout::core::sdl_window::SDLWindow& window);

    static SDL_Renderer* s_sdlRenderer;

    zbreakout::core::log::Log& m_log;
    SDL_Texture* m_sdlTexture;
};

}