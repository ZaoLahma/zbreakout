#pragma once

#include "layered_renderer.h"
#include "log.h"
#include "sdl_renderer.h"
#include "sdl_window.h"

// SDL2
#include <SDL_render.h>

namespace zbreakout::core::sdl_layered_renderer
{
class SDLLayeredRenderer : public layered_renderer::LayeredRenderer
{
public:
    SDLLayeredRenderer(zbreakout::core::log::Log& log, zbreakout::core::sdl_window::SDLWindow& window) : m_log(log), m_window(window) {}
    virtual ~SDLLayeredRenderer() = default;

    void renderFrame() override
    {
        LayeredRenderer::renderFrame();

        SDL_RenderPresent(m_sdlRenderer);
    }

    bool addLayer(uint32_t layer) override
    {
        if (m_layerRenderers.find(layer) == m_layerRenderers.end())
        {
            const auto renderer {std::make_shared<zbreakout::core::sdl_renderer::SDLRenderer>(m_log, m_window)};
            m_layerRenderers[layer] = renderer;

            m_sdlRenderer = renderer->getSDLRenderer();

            m_log.info(__func__, "Layer " + std::to_string(layer) + " added");
            return true;
        }

        m_log.error(__func__, "Layer " + std::to_string(layer) + " already exists");

        return false;
    }

private:
    zbreakout::core::log::Log& m_log;
    zbreakout::core::sdl_window::SDLWindow& m_window;

    SDL_Renderer* m_sdlRenderer {nullptr};
};

}