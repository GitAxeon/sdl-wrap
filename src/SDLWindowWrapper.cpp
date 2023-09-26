#include "SDLWindowWrapper.hpp"

#include <SDL3/SDL.h>

SDLWindowWrapper::SDLWindowWrapper(const WindowInfo& info)
{
    uint32_t flags = SDL_WINDOW_VULKAN;
    m_SDLWindow = SDL_CreateWindow(info.Title.c_str(), info.Width, info.Height, flags);

    if(m_SDLWindow == nullptr)
    {
        Log.Error("Created SDLWindowWrapper unsuccesfully");
        throw std::runtime_error("Failed to create Window");
    }

    Log.Info("Created SDLWindowWrapper");
}

SDLWindowWrapper::~SDLWindowWrapper()
{
    Log.Info("Destructed SDLWindowWrapper");
    SDL_DestroyWindow(m_SDLWindow);
}

SDL_Window* SDLWindowWrapper::GetNativeWindow() const
{
    return m_SDLWindow;
}

VkSurfaceKHR SDLWindowWrapper::CreateVulkanSurface(VkInstance instance)
{
    VkSurfaceKHR surface = nullptr;
    SDL_bool result = SDL_Vulkan_CreateSurface(m_SDLWindow, instance, &surface);

    if(result == SDL_FALSE)
    {
        Log.Error("SDL_Vulkan_CreateSurface failed");
        Log.Error(SDL_GetError());
        throw std::runtime_error("Failed to create VulkanSurface");
    }

    return surface;
}