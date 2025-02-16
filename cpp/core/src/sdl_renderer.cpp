#include "sdl_renderer.h"
#include "sdl_window.h"

// SDL2
#include <SDL_error.h>
#include <SDL_render.h>
#include <bitset>

namespace zbreakout::core::sdl_renderer
{

SDL_Renderer* SDLRenderer::s_sdlRenderer {nullptr};


// Craziness : Define a font using bitmaps instead of TTF
std::array<std::bitset<8>, 8> letterA =
{
    std::bitset<8>("00111100"), 
    std::bitset<8>("01100110"), 
    std::bitset<8>("01000010"), 
    std::bitset<8>("01111110"), 
    std::bitset<8>("01000010"), 
    std::bitset<8>("01000010"), 
    std::bitset<8>("01000010"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterB =
{
    std::bitset<8>("11111000"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("11111000"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("11111000"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterC =
{
    std::bitset<8>("00111100"), 
    std::bitset<8>("01000010"), 
    std::bitset<8>("01000000"), 
    std::bitset<8>("01000000"), 
    std::bitset<8>("01000000"), 
    std::bitset<8>("01000010"), 
    std::bitset<8>("00111100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterD =
{
    std::bitset<8>("11111000"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("11111000"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterE =
{
    std::bitset<8>("11111000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("11110000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("11111000"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterF =
{
    std::bitset<8>("11111000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("11110000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterG =
{
    std::bitset<8>("01111100"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10111110"), 
    std::bitset<8>("10000010"), 
    std::bitset<8>("10000010"), 
    std::bitset<8>("01111100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterH =
{
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("11111110"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterI =
{
    std::bitset<8>("00111100"), 
    std::bitset<8>("00010000"), 
    std::bitset<8>("00010000"), 
    std::bitset<8>("00010000"), 
    std::bitset<8>("00010000"), 
    std::bitset<8>("00010000"), 
    std::bitset<8>("00111100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterJ =
{
    std::bitset<8>("00111100"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("10001000"), 
    std::bitset<8>("01111100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterK =
{
    std::bitset<8>("10000100"), 
    std::bitset<8>("10001000"), 
    std::bitset<8>("10110000"), 
    std::bitset<8>("11000000"), 
    std::bitset<8>("10110000"), 
    std::bitset<8>("10001000"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterL =
{
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("11111000"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterM =
{
    std::bitset<8>("10000100"), 
    std::bitset<8>("11000110"), 
    std::bitset<8>("10100110"), 
    std::bitset<8>("10100110"), 
    std::bitset<8>("10100110"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterN =
{
    std::bitset<8>("10000100"), 
    std::bitset<8>("11000100"), 
    std::bitset<8>("10100100"), 
    std::bitset<8>("10010100"), 
    std::bitset<8>("10001100"), 
    std::bitset<8>("10000110"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterO =
{
    std::bitset<8>("01111100"), 
    std::bitset<8>("10000010"), 
    std::bitset<8>("10000010"), 
    std::bitset<8>("10000010"), 
    std::bitset<8>("10000010"), 
    std::bitset<8>("10000010"), 
    std::bitset<8>("01111100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterP =
{
    std::bitset<8>("11111000"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("11111000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterQ =
{
    std::bitset<8>("01111100"), 
    std::bitset<8>("10000010"), 
    std::bitset<8>("10000010"), 
    std::bitset<8>("10111110"), 
    std::bitset<8>("10000010"), 
    std::bitset<8>("10000010"), 
    std::bitset<8>("01111110"), 
    std::bitset<8>("00000001")
};

std::array<std::bitset<8>, 8> letterR =
{
    std::bitset<8>("11111000"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("11111000"), 
    std::bitset<8>("10001000"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterS =
{
    std::bitset<8>("01111100"), 
    std::bitset<8>("10000010"), 
    std::bitset<8>("10000000"), 
    std::bitset<8>("01111100"), 
    std::bitset<8>("00000010"), 
    std::bitset<8>("00000001"), 
    std::bitset<8>("01111100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterT =
{
    std::bitset<8>("11111100"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterU =
{
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("01111100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterV =
{
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("01111100"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterW =
{
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10100100"), 
    std::bitset<8>("10100100"), 
    std::bitset<8>("10100100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("00000000")   
};


std::array<std::bitset<8>, 8> letterX =
{
    std::bitset<8>("10000001"), 
    std::bitset<8>("01000010"), 
    std::bitset<8>("00100100"), 
    std::bitset<8>("00011000"), 
    std::bitset<8>("00100100"), 
    std::bitset<8>("01000010"), 
    std::bitset<8>("10000001"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterY =
{
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("10000100"), 
    std::bitset<8>("01111100"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letterZ =
{
    std::bitset<8>("11111110"), 
    std::bitset<8>("00000100"), 
    std::bitset<8>("00001000"), 
    std::bitset<8>("00010000"), 
    std::bitset<8>("00100000"), 
    std::bitset<8>("01000000"), 
    std::bitset<8>("11111110"), 
    std::bitset<8>("00000000")   
};

std::array<std::bitset<8>, 8> letter0 =
{
    std::bitset<8>("01111100"),
    std::bitset<8>("10000010"),
    std::bitset<8>("10010010"),
    std::bitset<8>("10010010"),
    std::bitset<8>("10010010"),
    std::bitset<8>("10000010"),
    std::bitset<8>("01111100"),
    std::bitset<8>("00000000")
};

std::array<std::bitset<8>, 8> letter1 =
{
    std::bitset<8>("00001000"),
    std::bitset<8>("00011000"),
    std::bitset<8>("00101000"),
    std::bitset<8>("00001000"),
    std::bitset<8>("00001000"),
    std::bitset<8>("00001000"),
    std::bitset<8>("00111110"),
    std::bitset<8>("00000000")
};

std::array<std::bitset<8>, 8> letter2 =
{
    std::bitset<8>("01111100"),
    std::bitset<8>("10000010"),
    std::bitset<8>("00000010"),
    std::bitset<8>("00011100"),
    std::bitset<8>("00100000"),
    std::bitset<8>("01000000"),
    std::bitset<8>("11111110"),
    std::bitset<8>("00000000")
};

std::array<std::bitset<8>, 8> letter3 =
{
    std::bitset<8>("01111100"),
    std::bitset<8>("10000010"),
    std::bitset<8>("00000010"),
    std::bitset<8>("00111100"),
    std::bitset<8>("00000010"),
    std::bitset<8>("10000010"),
    std::bitset<8>("01111100"),
    std::bitset<8>("00000000")
};

std::array<std::bitset<8>, 8> letter4 =
{
    std::bitset<8>("00001100"),
    std::bitset<8>("00010100"),
    std::bitset<8>("00100100"),
    std::bitset<8>("01000100"),
    std::bitset<8>("11111110"),
    std::bitset<8>("00000100"),
    std::bitset<8>("00000100"),
    std::bitset<8>("00000000")
};

std::array<std::bitset<8>, 8> letter5 =
{
    std::bitset<8>("11111110"),
    std::bitset<8>("10000000"),
    std::bitset<8>("10000000"),
    std::bitset<8>("11111100"),
    std::bitset<8>("00000010"),
    std::bitset<8>("10000010"),
    std::bitset<8>("01111100"),
    std::bitset<8>("00000000")
};

std::array<std::bitset<8>, 8> letter6 =
{
    std::bitset<8>("01111100"),
    std::bitset<8>("10000010"),
    std::bitset<8>("10000000"),
    std::bitset<8>("11111100"),
    std::bitset<8>("10000010"),
    std::bitset<8>("10000010"),
    std::bitset<8>("01111100"),
    std::bitset<8>("00000000")
};

std::array<std::bitset<8>, 8> letter7 =
{
    std::bitset<8>("11111110"),
    std::bitset<8>("00000010"),
    std::bitset<8>("00000100"),
    std::bitset<8>("00001000"),
    std::bitset<8>("00010000"),
    std::bitset<8>("00100000"),
    std::bitset<8>("01000000"),
    std::bitset<8>("00000000")
};

std::array<std::bitset<8>, 8> letter8 =
{
    std::bitset<8>("01111100"),
    std::bitset<8>("10000010"),
    std::bitset<8>("10000010"),
    std::bitset<8>("01111100"),
    std::bitset<8>("10000010"),
    std::bitset<8>("10000010"),
    std::bitset<8>("01111100"),
    std::bitset<8>("00000000")
};

std::array<std::bitset<8>, 8> letter9 =
{
    std::bitset<8>("01111100"),
    std::bitset<8>("10000010"),
    std::bitset<8>("10000010"),
    std::bitset<8>("01111110"),
    std::bitset<8>("00000010"),
    std::bitset<8>("10000010"),
    std::bitset<8>("01111100"),
    std::bitset<8>("00000000")
};

std::array<std::bitset<8>, 8> blank =
{
    std::bitset<8>("00000000"),
    std::bitset<8>("00000000"),
    std::bitset<8>("00000000"),
    std::bitset<8>("00000000"),
    std::bitset<8>("00000000"),
    std::bitset<8>("00000000"),
    std::bitset<8>("00000000"),
    std::bitset<8>("00000000")
};


std::map<char, std::array<std::bitset<8>, 8>> characterToLetter {
    {'A', letterA},
    {'B', letterB},
    {'C', letterC},
    {'D', letterD},
    {'E', letterE},
    {'F', letterF},
    {'G', letterG},
    {'H', letterH},
    {'I', letterI},
    {'J', letterJ},
    {'K', letterK},
    {'L', letterL},
    {'M', letterM},
    {'N', letterN},
    {'O', letterO},
    {'P', letterP},
    {'Q', letterQ},
    {'R', letterR},
    {'S', letterS},
    {'T', letterT},
    {'U', letterU},
    {'V', letterV},
    {'W', letterW},
    {'X', letterX},
    {'Y', letterY},
    {'Z', letterZ},
    {'0', letter0},
    {'1', letter1},
    {'2', letter2},
    {'3', letter3},
    {'4', letter4},
    {'5', letter5},
    {'6', letter6},
    {'7', letter7},
    {'8', letter8},
    {'9', letter9},
    {' ', blank},
    {'\n', blank},
    {'\t', blank}
};


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

void SDLRenderer::renderText(const std::string& text, const core::renderer::ScreenPosition& position, const core::renderer::Color& color, uint32_t scale)
{
    SDL_SetRenderTarget(s_sdlRenderer, m_sdlTexture);

    SDL_SetRenderDrawColor(s_sdlRenderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect {position.x, position.y, 0, 0};

    uint32_t charCounter {0};
    // Iterate over the text to upper case
    std::string upperCaseText = text;
    std::transform(upperCaseText.begin(), upperCaseText.end(), upperCaseText.begin(), ::toupper);
    for (char c : upperCaseText)
    {
        auto letter = characterToLetter.find(c);
        if (letter != characterToLetter.end())
        {
            for (int y = 0; y < 8; ++y)
            {
                for (int x = 7; x >= 0; --x)  // Loop from right to left (from 7 to 0)
                {
                    if (letter->second[y][x])
                    {
                        // Handle scale
                        rect.w = scale;
                        rect.h = scale;
                        rect.x = position.x + (7 - x) + charCounter * 8 * scale;  // Adjust x to account for reversed rendering
                        rect.y = position.y + y * scale;
                        SDL_RenderFillRect(s_sdlRenderer, &rect);
                    }
                }
            }
        }
        else
        {
            m_log.error(__func__, "Character not found: " + std::string(1, c));
        }
    
        charCounter++;
    }
}

void SDLRenderer::renderFrame()
{
    SDL_SetRenderTarget(s_sdlRenderer, nullptr);
    SDL_RenderCopy(s_sdlRenderer, m_sdlTexture, nullptr, nullptr);

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