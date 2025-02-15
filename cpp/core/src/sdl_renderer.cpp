#include "sdl_renderer.h"
#include "sdl_window.h"

// SDL2
#include <SDL_error.h>
#include <SDL_render.h>

namespace zbreakout::core::sdl_renderer
{

SDL_Renderer* SDLRenderer::s_sdlRenderer {nullptr};

SDLRenderer::SDLRenderer(
    zbreakout::core::log::Log& log,
    zbreakout::core::sdl_window::SDLWindow& window) : m_log(log)
{
    SDLRenderer::initializeSDLRenderer(window);

    m_sdlTexture = 
        SDL_CreateTexture(
            s_sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
            window.getWindowResolution().width, window.getWindowResolution().height);
}

SDLRenderer::~SDLRenderer()
{
    m_log.info(__func__, "Destroying SDL renderer");
    SDL_DestroyTexture(m_sdlTexture);
    m_log.info(__func__, "SDL texture destroyed");

    if (nullptr != s_sdlRenderer)
    {
        SDL_DestroyRenderer(s_sdlRenderer);
        s_sdlRenderer = nullptr;
        m_log.info(__func__, "SDL renderer destroyed");
    }
}

void SDLRenderer::fillCircle(const core::renderer::ScreenPosition& position, int radius, const core::renderer::Color& color)
{
    SDL_SetRenderTarget(s_sdlRenderer, m_sdlTexture);

    SDL_SetRenderDrawColor(s_sdlRenderer, color.r, color.g, color.b, color.a);

    const uint32_t fullCirleDegrees {360};

    for (uint32_t sweep {0}; sweep < radius; ++sweep)
    {
        for (uint32_t degrees {0}; degrees < fullCirleDegrees; ++degrees)
        {
            const double angle {2 * M_PI * degrees / fullCirleDegrees};
            const int x {static_cast<int>(position.x + sweep * cos(angle))};
            const int y {static_cast<int>(position.y + sweep * sin(angle))};
            
            if (SDL_RenderDrawPoint(s_sdlRenderer, x, y) != 0)
            {
                m_log.error(__func__, "Failed to draw circle: " + std::string(SDL_GetError()));
            }
        }
    }
}

void SDLRenderer::fillRectangle(const core::renderer::ScreenPosition& position, int width, int height, const core::renderer::Color& color)
{
    SDL_SetRenderTarget(s_sdlRenderer, m_sdlTexture);

    SDL_SetRenderDrawColor(s_sdlRenderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect {position.x, position.y, width, height};
    
    if (SDL_RenderFillRect(s_sdlRenderer, &rect) != 0)
    {
        m_log.error(__func__, "Failed to draw rectangle: " + std::string(SDL_GetError()));
    }
}

void SDLRenderer::renderFrame()
{
    SDL_SetRenderTarget(s_sdlRenderer, nullptr);
    SDL_RenderCopy(s_sdlRenderer, m_sdlTexture, nullptr, nullptr);

    // TODO: Check how to properly clear the screen between frames
    SDL_SetRenderTarget(s_sdlRenderer, m_sdlTexture);
    SDL_SetRenderDrawColor(s_sdlRenderer, 0, 0, 0, 0);
    SDL_RenderClear(s_sdlRenderer);
}

void SDLRenderer::initializeSDLRenderer(zbreakout::core::sdl_window::SDLWindow& window)
{
    if (nullptr == s_sdlRenderer)
    {
        s_sdlRenderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    }
}

}