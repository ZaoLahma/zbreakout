#pragma once

#include "renderer.h"

// Standard library
#include <cstdint>
#include <map>
#include <memory>
#include <optional>

namespace zbreakout::core::layered_renderer
{

class LayeredRenderer : public renderer::FrameRenderer
{
public:
    LayeredRenderer() = default;
    virtual ~LayeredRenderer() = default;

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