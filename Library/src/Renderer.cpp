#include "debug/Log.hpp"
#include "../include/sdlw/Renderer.hpp"
#include "../include/sdlw/Window.hpp"

#include "../include/sdlw/Rect.hpp"
#include "../include/sdlw/Texture.hpp"

#include <exception>

SDLW_NAMESPACE_BEGIN

Renderer::Renderer(Window &window)
    : m_Window(window), m_Renderer(nullptr), m_ClearColor({0, 0, 0, 255}), m_DrawColor({255, 0, 255, 255})
{
    uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    m_Renderer = SDL_CreateRenderer(window.GetNativeWindow(), nullptr, flags);

    if(m_Renderer == nullptr)
    {
        Log.Error("Created Renderer unsuccesfully");
        throw std::runtime_error("Failed to create Window");
    }

    ApplyColor(m_DrawColor);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_Renderer);
}

SDL_Renderer* Renderer::GetHandle() const
{
    return m_Renderer;
}

Window& Renderer::GetWindow() const
{
    return m_Window;
}

void Renderer::Present()
{
    SDL_RenderPresent(m_Renderer);
}

void Renderer::SetClearColor(const SDL_Color &color)
{
    m_ClearColor = color;
}

void Renderer::SetDrawColor( const SDL_Color& color)
{
    m_DrawColor = color;
    ApplyColor(color);
}

void Renderer::Clear()
{
    ApplyColor(m_ClearColor);
    SDL_RenderClear(m_Renderer);
    ApplyColor(m_DrawColor);
}

void Renderer::RenderTexture(Texture& texture, const Optional<FRect>& srcRect, const Optional<FRect>& dstRect)
{        
    FRect destination(
        dstRect ? dstRect->GetX() : 0, 
        dstRect ? dstRect->GetY() : 0, 
        dstRect ? dstRect->GetWidth() : texture.GetWidth(), 
        dstRect ? dstRect->GetHeight() : texture.GetHeight()
    );
    // ToDo validity checks for rects

    SDL_RenderTexture(
        m_Renderer,
        texture.GetHandle(),
        srcRect ? &*srcRect : nullptr,
        dstRect ? &*dstRect : nullptr
    );
};

void Renderer::RenderTexture(Texture& texture, const FPoint& dstPoint)
{
    FRect destination(
        dstPoint.x,
        dstPoint.y,
        texture.GetWidth(),
        texture.GetHeight()
    );

    RenderTexture(texture, NullOpt, destination);
}

void Renderer::RenderTexture(Texture& texture)
{        
    RenderTexture(texture, NullOpt, NullOpt);
};

void Renderer::Rectangle(const FRect& rectangle, bool fill)
{
    if(fill)
        SDL_RenderFillRect(m_Renderer, &rectangle);
    else
        SDL_RenderRect(m_Renderer, &rectangle);
}

void Renderer::ApplyColor(const SDL_Color& color)
{
    SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
}

SDLW_NAMESPACE_END