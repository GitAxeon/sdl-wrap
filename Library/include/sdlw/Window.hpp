#pragma once

#include "Context.hpp"
#include "Event.hpp"

// #include "../Vulkan/VulkanInstance.hpp"

// #include <SDL3/SDL_vulkan.h>
// #include <Vulkan/vulkan.hpp>

#include <SDL3/SDL.h>

#include <string>

namespace sdlw
{
    struct WindowInfo
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowInfo()
            : Title("default"), Width(720), Height(300) {}

        WindowInfo(const std::string& title, unsigned int width, unsigned int height)
            : Title(title), Width(width), Height(height) {}
    };

    class Context;
    class Window
    {
    public:
        Window(Context& context, const WindowInfo &info);
        ~Window();

        bool KeepOpen() const;
        void Close();
        // VkSurfaceKHR CreateVulkanSurface(VkInstance instance);

        bool SetEventCallback(const EventCallback& callback);

        void ChangeTitle(const std::string& title);

        void SetWidth(unsigned int width);
        void SetHeight(unsigned int height);
        void SetSize(unsigned int width, unsigned int height);
        
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;

        void SetTransparency(float value);
        uint32_t GetFlags() const;
        
        SDL_Window* GetNativeWindow() const;
        WindowID GetWindowID() const;
        Context& GetContext();

        bool Ok() const;

    private: 
        SDL_Window* m_SDLWindow;
        Context& m_Context;
        WindowInfo m_Info;
        bool m_Open;

        bool m_Ok;
    };
}