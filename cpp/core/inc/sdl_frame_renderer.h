#pragma once

#include "frame_renderer.h"
#include "log.h"
#include "sdl_renderer.h"
#include "sdl_window.h"

// SDL2
#include <SDL_render.h>

namespace zbreakout::core::sdl_layered_renderer
{
class SDLLayeredFrameRenderer : public layered_renderer::LayeredFrameRenderer
{
public:
    SDLLayeredFrameRenderer(zbreakout::core::log::Log& log, zbreakout::core::sdl_window::SDLWindow& window) : m_log(log), m_window(window) {}
    virtual ~SDLLayeredFrameRenderer() = default;

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