#include "../include/sdlw/Context.hpp"
#include "../include/sdlw/Window.hpp"
#include "Event_Internal.hpp"

#include "debug/Log.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <exception>

SDLW_NAMESPACE_BEGIN

Context::Context(uint32_t sdlInitFlags)
{
    int result = SDL_Init(sdlInitFlags);

    if(result != 0)
    {
        Log.Error("Failed to initialize SDL", GetError());
        throw std::runtime_error("Failed to initialize SDL");
    }
}

Context::~Context()
{
    SDL_Vulkan_UnloadLibrary();
    SDL_Quit();
}

const char *Context::GetError() const
{
    return SDL_GetError();
}

// void Context::EnableVulkan()
// {
//     if(SDL_Vulkan_LoadLibrary(nullptr) != 0)
//     {
//         Log.Error("Failed to load Vulkan");
//         throw std::runtime_error("Failed to load Vulkan");
//     }

//     Log.Info("Vulkan Library enabled");
// }

// std::vector<const char*> Context::GetVulkanInstanceExtensions()
// {
//     uint32_t SDLExtensionCount = 0;
//     SDL_bool extensionResult = SDL_Vulkan_GetInstanceExtensions(&SDLExtensionCount, nullptr);

//     if(extensionResult == SDL_FALSE)
//     {
//         Log.Error("SDL_Vulkan_GetInstanceExtensions failed for extension count");
//         Log.Error("SDL Error:" , SDL_GetError());

//         throw std::runtime_error("Failed to retrieve Vulkan extensions");
//     }

//     std::vector<const char*> result;
//     result.resize(SDLExtensionCount);

//     extensionResult = SDL_Vulkan_GetInstanceExtensions(&SDLExtensionCount, result.data()); 
    
//     if(extensionResult == SDL_FALSE)
//     {
//         Log.Error("SDL_Vulkan_GetInstanceExtensions for extension names failed");
//         Log.Error("SDL Error:" , SDL_GetError());
        
//         throw std::runtime_error("Failed to retrieve Vulkan extensions");
//     }

//     return result;
// }

Window Context::CreateWindow(const WindowInfo& info)
{
    return Window(*this, info);
}

bool Context::SetWindowEventCallback(WindowID id, const EventCallback& callback)
{
    if(m_EventCallbacks.count(id) == 0)
    {
        m_EventCallbacks[id] = callback;
        return true;
    }

    return false;
}

bool Context::Ok() const
{
    return m_Ok;
}

int Context::PollEvents()
{
    int handledEvents = 0;

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        Event event(sdlEvent);
        event.WindowID = GetWindowID(sdlEvent);

        if(m_CustomEventCallback != nullptr && m_CustomEventCallback(event))
        {
            handledEvents++;
            continue;
        }

        if(DispatchEvent(event))
            handledEvents++;
    }

    return handledEvents;
}

bool Context::DispatchEvent(Event& event)
{
    if(event.WindowID.has_value())
    {
        if(m_EventCallbacks.count(*event.WindowID) != 0)
        {
            return m_EventCallbacks[*event.WindowID](event);
        }
        
        return false;
    }

    for(auto& callback : m_EventCallbacks)
    {
        callback.second(event);
    }

    return true;
}

void Context::SetCustomEventCallback(CustomEventCallback callback)
{
    m_CustomEventCallback = callback;
}

SDLW_NAMESPACE_END