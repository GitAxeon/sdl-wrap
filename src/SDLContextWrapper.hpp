#pragma once

#include "SDL3/SDL_init.h"

#include <vector>

class SDLContextWrapper
{
public:
    explicit SDLContextWrapper(uint32_t sdl_initFlags = SDL_INIT_EVERYTHING);

    void EnableVulkan();
    std::vector<const char*> GetVulkanInstanceExtensions();
    
    ~SDLContextWrapper();

    const char* GetError() const;
};