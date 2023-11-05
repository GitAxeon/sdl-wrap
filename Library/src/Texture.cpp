#include "../include/sdlw/Texture.hpp"
#include "debug/Log.hpp"

#include <STB/stb_image.h>

namespace sdlw
{
    Texture::Texture(Renderer& renderer, int width, int height, uint32_t format, int access)
        : m_Texture(nullptr), m_Width(width), m_Height(height), m_Format(format)
    {
        m_Texture = SDL_CreateTexture(
            renderer.GetHandle(),
            format,
            access,
            width,
            height
        );

        if(m_Texture == nullptr)
        {
            Log.Error("Texture creation failed");
            throw std::runtime_error("Texture creation failed");
        }

        Log.Info("Texture created successfully");
    }

    Texture::Texture(Renderer& renderer, std::string filepath, ImageFormat format)
    {
        if(filepath.length() == 0)
        {
            Log.Error("Texture: Filepath was empty");
            throw std::runtime_error("Texture creation failed");
        }
        
        int channels;

        uint8_t* pixels = stbi_load(
            filepath.c_str(),
            &m_Width,
            &m_Height,
            &channels,
            (format == ImageFormat::RGB ? STBI_rgb : STBI_rgb_alpha)
        );
        m_Format = SDL_PIXELFORMAT_RGBA32;

        if(pixels == nullptr)
        {
            Log.Error("Texture: Failed to read pixeldata from ", filepath);
            throw std::runtime_error("Texture creation failed");
        }

        if(channels != 4)
        {
            Log.Error("Texture: RGB not supported");
            throw std::runtime_error("Texture: Loading RGB format is not supported");
        }

        Log.Info("Pixels loaded from file ", filepath);

        m_Texture = SDL_CreateTexture(
            renderer.GetHandle(),
            SDL_PIXELFORMAT_RGBA32,
            SDL_TEXTUREACCESS_STATIC,
            m_Width,
            m_Height
        );

        if(m_Texture == nullptr)
        {
            Log.Error("Texture creation failed");
            throw std::runtime_error("Texture creation failed");
        } 
        
        // The number of bytes in a row of pixeldata
        m_Pitch = m_Width * channels;

        Update(NullOpt, pixels);

        free(pixels);

        Log.Info("Texture created successfully");
    }

    Texture::~Texture()
    {
        SDL_DestroyTexture(m_Texture);
    }

    SDL_Texture* Texture::GetHandle() const
    {
        return m_Texture;
    }

    int Texture::GetWidth() const
    {
        return m_Width;
    }
    
    int Texture::GetHeight() const
    {
        return m_Height;
    }
    
    uint32_t Texture::GetFormat() const
    {
        return m_Format;
    }

    bool Texture::Update(const Optional<Rect>& rect, const void* pixels)
    {
        if(pixels == nullptr)
            return false;
            
        int result = SDL_UpdateTexture(
            m_Texture,
            rect ? &*rect : nullptr,
            pixels,
            m_Pitch
        );

        if(result != 0)
        {
            Log.Error("Failed to update texture: ");
        }

        return result;
    }
}