#include "debug/Log.hpp"
#include "../include/sdlw/Renderer.hpp"
#include "../include/sdlw/Window.hpp"

#include "../include/sdlw/Rect.hpp"
#include "../include/sdlw/Texture.hpp"

#include <exception>

SDLW_NAMESPACE_BEGIN

Renderer::Renderer(Window &window)
    : m_Window(window), m_ClearColor({0, 0, 0, 255})
{
    uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    m_Renderer = SDL_CreateRenderer(window.GetNativeWindow(), nullptr, flags);

    if(m_Renderer == nullptr)
    {
        Log.Error("Created Renderer unsuccesfully");
        throw std::runtime_error("Failed to create Window");
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_Renderer);
}

SDL_Renderer* Renderer::GetHandle() const
{
    return m_Renderer;
}

void Renderer::Present()
{
    SDL_RenderPresent(m_Renderer);
}

void Renderer::SetClearColor(const SDL_Color &color)
{
    m_ClearColor = color;
}

void Renderer::Clear()
{
    SDL_SetRenderDrawColor(m_Renderer, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
    SDL_RenderClear(m_Renderer);
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

SDLW_NAMESPACE_END