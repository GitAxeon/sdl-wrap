#pragma once
#include "../src/core/Macro.hpp"
#include "Event.hpp"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>

#include <map>

namespace sdlw
{
    class Window;
    struct WindowInfo;
    
    using CustomEventCallback = std::function<bool(SDL_Event &e)>;

    class API Context
    {
    public:
        explicit Context(uint32_t sdl_initFlags = SDL_INIT_EVERYTHING);
        Context(const Context&) = delete;

        ~Context();
        
        const char* GetError() const;

        Window CreateWindow(const WindowInfo &info);

        int PollEvents();

        // void EnableVulkan();
        // std::vector<const char*> GetVulkanInstanceExtensions();
        bool Ok() const;
        void SetCustomEventCallback(CustomEventCallback callback);

    private:
        friend class Window;
        bool SetWindowEventCallback(WindowID id, const EventCallback& callback);
        bool DispatchEvent(SDL_Event &e);

    private:
        std::map<WindowID, EventCallback> m_EventCallbacks;
        CustomEventCallback m_CustomEventCallback;

        bool m_Ok;
    };
}