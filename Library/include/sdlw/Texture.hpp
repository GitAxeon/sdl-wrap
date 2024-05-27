#pragma once
#include "../src/core/Macro.hpp"

#include "Renderer.hpp"
#include "Optional.hpp"
#include "Rect.hpp"

#include <SDL3/SDL_render.h>

#include <string>

namespace sdlw
{
    class Texture
    {
    public:
        enum class ImageFormat { RGB, RGBA };

        Texture(Renderer& renderer, int width, int height, uint32_t format, int access = SDL_TEXTUREACCESS_STATIC);
        Texture(Renderer& renderer, std::string filepath, ImageFormat format = ImageFormat::RGBA);
        ~Texture();

        SDL_Texture* GetHandle() const;
        int GetWidth() const;
        int GetHeight() const;
        uint32_t GetFormat() const;

        bool Update(const Optional<Rect>& rect, const void* pixels);
    private:
        SDL_Texture* m_Texture;
        int m_Width;
        int m_Height;
        uint32_t m_Format;
        int m_Pitch;
    };
}