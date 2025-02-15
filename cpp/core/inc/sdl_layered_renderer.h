#pragma once

#include "layered_renderer.h"
#include "log.h"
#include "sdl_renderer.h"
#include "sdl_window.h"

namespace zbreakout::core::sdl_layered_renderer
{
class SDLLayeredRenderer : public layered_renderer::LayeredRenderer
{
public:
    SDLLayeredRenderer(zbreakout::core::log::Log& log, zbreakout::core::sdl_window::SDLWindow& window) : m_log(log), m_window(window) {}
    virtual ~SDLLayeredRenderer() = default;

    bool addLayer(uint32_t layer) override
    {
        if (m_renderers.find(layer) == m_renderers.end())
        {
            m_renderers[layer] = std::make_shared<zbreakout::core::sdl_renderer::SDLRenderer>(m_log, m_window);
            m_log.info(__func__, "Layer " + std::to_string(layer) + " added");
            return true;
        }

        m_log.error(__func__, "Layer " + std::to_string(layer) + " already exists");

        return false;
    }

private:
    zbreakout::core::log::Log& m_log;
    zbreakout::core::sdl_window::SDLWindow& m_window;
};

}