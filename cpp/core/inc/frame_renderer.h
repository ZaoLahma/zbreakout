#pragma once

#include "renderer.h"

// Standard library
#include <cstdint>
#include <map>
#include <memory>
#include <optional>

namespace zbreakout::core::layered_renderer
{

/**
 * Layered renderer
 */
class LayeredFrameRenderer : public renderer::FrameRenderer
{
public:
    LayeredFrameRenderer() = default;
    virtual ~LayeredFrameRenderer() = default;

    void renderFrame() override
    {
        // Render sorted by layer
        for (const auto& [layer, renderer] : m_layerRenderers)
        {
            renderer->renderFrame();
        }
    }

    /**
     * Add a new layer to the renderer - must be called before getRendererForLayer for the layer
     *
     * @return true if the layer was added
     */
    virtual bool addLayer(uint32_t layer) = 0;

    /**
     * Get the renderer for the given layer, if it has been added with addLayer
     *
     * @param layer The layer to get the renderer for
     * @return A shared pointer to the renderer for the given layer, or an empty optional
     */
    std::optional<std::shared_ptr<renderer::Renderer>> getRendererForLayer(uint32_t layer)
    {
        if (m_layerRenderers.find(layer) != m_layerRenderers.end())
        {
            return m_layerRenderers[layer];
        }

        return {};
    }

protected:

    std::map<uint32_t /*layer*/, std::shared_ptr<renderer::Renderer>> m_layerRenderers;
};

}