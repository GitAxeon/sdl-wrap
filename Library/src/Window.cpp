#include "../include/sdlw/Window.hpp"
#include "../include/sdlw/Context.hpp"

#include "debug/Log.hpp"

#include <exception>

SDLW_NAMESPACE_BEGIN

Window::Window(Context& context, const WindowInfo &info) : m_SDLWindow(nullptr), m_Context(context), m_Info(info), m_Open(true)
{
    m_Context = context;

    m_SDLWindow = SDL_CreateWindow(info.Title.c_str(), info.Width, info.Height, info.Flags);

    if(m_SDLWindow == nullptr)
    {
        Log.Error("Created SDLWindowWrapper unsuccesfully");
        throw std::runtime_error("Failed to create Window");
        
        m_Open = false;
    }
    
    m_Open = true;
    Log.Info("Created Window [id ", GetWindowID(), "]");
}

Window::~Window()
{
    Log.Info("Destructed SDLWindowWrapper");
    SDL_DestroyWindow(m_SDLWindow);
}

SDL_Window *Window::GetNativeWindow() const
{
    return m_SDLWindow;
}

bool Window::KeepOpen() const 
{
    return m_Open;
}

void Window::Close()
{
    Log.Info("Close requested for WindowID: ", GetWindowID());
    m_Open = false;
}

WindowID Window::GetWindowID() const
{
    return SDL_GetWindowID(m_SDLWindow);
}

Context& Window::GetContext()
{
    return m_Context;
}

bool Window::SetEventCallback(const EventCallback& callback)
{
    return m_Context.SetWindowEventCallback(GetWindowID(), callback);
}

void Window::ChangeTitle(const std::string& title)
{
    m_Info.Title = title;
    SDL_SetWindowTitle(m_SDLWindow, title.c_str());
}

void Window::SetWidth(unsigned int width)
{
    m_Info.Width = width;
    SDL_SetWindowSize(m_SDLWindow, width, m_Info.Height);
}
void Window::SetHeight(unsigned int height)
{
    m_Info.Height = height;
    SDL_SetWindowSize(m_SDLWindow, m_Info.Width, height);
}
void Window::SetSize(unsigned int width, unsigned int height)
{
    m_Info.Width = width;
    m_Info.Height = height;
    SDL_SetWindowSize(m_SDLWindow, width, height);
}

unsigned int sdlw::Window::GetWidth() const
{
    return m_Info.Width;
}

unsigned int sdlw::Window::GetHeight() const
{
    return m_Info.Height;
}

bool Window::Ok() const
{
    return m_Ok;
}

void Window::SetTransparency(float value)
{
    value = 1.0f - value;

    SDL_SetWindowOpacity(m_SDLWindow, value);
}

uint32_t Window::GetFlags() const
{
    return SDL_GetWindowFlags(m_SDLWindow);
}

// VkSurfaceKHR Window::CreateVulkanSurface(VkInstance instance)
// {
//     VkSurfaceKHR surface = nullptr;
//     SDL_bool result = SDL_Vulkan_CreateSurface(m_SDLWindow, instance, &surface);

//     if(result == SDL_FALSE)
//     {
//         Log.Error("SDL_Vulkan_CreateSurface failed");
//         Log.Error(SDL_GetError());
//         throw std::runtime_error("Failed to create VulkanSurface");
//     }

//     return surface;
// }

SDLW_NAMESPACE_END