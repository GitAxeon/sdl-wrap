#pragma once

#include "../src/core/Macro.hpp"
#include "Optional.hpp"
#include "Rect.hpp"
#include "Point.hpp"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_pixels.h>


namespace sdlw
{
    class Window;
    class Texture;

    class API Renderer
    {
    public:
        explicit Renderer(Window &window);
        ~Renderer();
        SDL_Renderer* GetHandle() const;

        void SetClearColor(const SDL_Color& color);
        void Clear();
        void Present();

        void RenderTexture(Texture& texture, const Optional<FRect>& srcRect, const Optional<FRect>& dstRect);
        void RenderTexture(Texture& texture, const FPoint& dstPoint);
        void RenderTexture(Texture& texture);

    private:
        Window& m_Window;
        SDL_Renderer* m_Renderer;
        SDL_Color m_ClearColor;
    };
}