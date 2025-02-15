#include "sdl_renderer.h"

// SDL2
#include <SDL_error.h>
#include <SDL_render.h>

namespace zbreakout::core::sdl_renderer
{

SDLRenderer::SDLRenderer(zbreakout::core::log::Log& log, SDL_Window* window) : m_log(log), m_sdlRenderer{SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)}
{
}

void SDLRenderer::fillCircle(const core::renderer::ScreenPosition& position, int radius, const core::renderer::Color& color)
{
    SDL_SetRenderDrawColor(m_sdlRenderer, color.r, color.g, color.b, color.a);

    const uint32_t fullCirleDegrees {360};

    for (uint32_t degrees {0}; degrees < fullCirleDegrees; ++degrees)
    {
        const double angle {2 * M_PI * degrees / fullCirleDegrees};
        const int x {static_cast<int>(position.x + radius * cos(angle))};
        const int y {static_cast<int>(position.y + radius * sin(angle))};
        
        if (SDL_RenderDrawPoint(m_sdlRenderer, x, y) != 0)
        {
            m_log.error(__func__, "Failed to draw circle: " + std::string(SDL_GetError()));
        }
    }
}

void SDLRenderer::fillRectangle(const core::renderer::ScreenPosition& position, int width, int height, const core::renderer::Color& color)
{
    SDL_SetRenderDrawColor(m_sdlRenderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect {position.x, position.y, width, height};
    
    if (SDL_RenderFillRect(m_sdlRenderer, &rect) != 0)
    {
        m_log.error(__func__, "Failed to draw rectangle: " + std::string(SDL_GetError()));
    }
}

void SDLRenderer::renderScene()
{
    SDL_RenderPresent(m_sdlRenderer);
}

}