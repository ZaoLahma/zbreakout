#pragma once

#include "log.h"
#include "renderer.h"

struct SDL_Renderer;
struct SDL_Window;

namespace zbreakout::core::sdl_renderer
{

class SDLRenderer : public zbreakout::core::renderer::Renderer
{
public:
    SDLRenderer(zbreakout::core::log::Log& log, SDL_Window* window);
    ~SDLRenderer() = default;
    void fillCircle(const core::renderer::ScreenPosition& position, int radius, const core::renderer::Color& color) override;
    void fillRectangle(const core::renderer::ScreenPosition& position, int width, int height, const core::renderer::Color& color) override;

    void renderScene() override;

private:
    zbreakout::core::log::Log& m_log;
    SDL_Renderer* m_sdlRenderer;
};

}