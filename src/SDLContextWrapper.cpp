#include "SDLContextWrapper.hpp"

#include "../debug/Log.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <exception>

SDLContextWrapper::SDLContextWrapper(uint32_t sdlInitFlags)
{
    int result = SDL_Init(sdlInitFlags);

    if(result != 0)
    {
        Log.Error("Failed to initialize SDL", GetError());
        throw std::runtime_error("Failed to initialize SDL");
    }
}

SDLContextWrapper::~SDLContextWrapper()
{
    SDL_Vulkan_UnloadLibrary();
    SDL_Quit();
}

void SDLContextWrapper::EnableVulkan()
{
    if(SDL_Vulkan_LoadLibrary(nullptr) != 0)
    {
        Log.Error("Failed to load Vulkan");
        throw std::runtime_error("Failed to load Vulkan");
    }

    Log.Info("Vulkan Library enabled");
}

std::vector<const char*> SDLContextWrapper::GetVulkanInstanceExtensions()
{
    uint32_t SDLExtensionCount = 0;
    SDL_bool extensionResult = SDL_Vulkan_GetInstanceExtensions(&SDLExtensionCount, nullptr);

    if(extensionResult == SDL_FALSE)
    {
        Log.Error("SDL_Vulkan_GetInstanceExtensions failed for extension count");
        Log.Error("SDL Error:" , SDL_GetError());

        throw std::runtime_error("Failed to retrieve Vulkan extensions");
    }

    std::vector<const char*> result;
    result.resize(SDLExtensionCount);

    extensionResult = SDL_Vulkan_GetInstanceExtensions(&SDLExtensionCount, result.data()); 
    
    if(extensionResult == SDL_FALSE)
    {
        Log.Error("SDL_Vulkan_GetInstanceExtensions for extension names failed");
        Log.Error("SDL Error:" , SDL_GetError());
        
        throw std::runtime_error("Failed to retrieve Vulkan extensions");
    }

    return result;
}

const char* SDLContextWrapper::GetError() const
{
    return SDL_GetError();
}