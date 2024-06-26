// Public API
#include "../include/sdlw/Event.hpp"

// Internal API
#include "Event_Internal.hpp"

SDLW_NAMESPACE_BEGIN

std::optional<WindowID> GetWindowID(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_EVENT_USER:
            return event.user.windowID;
        case SDL_EVENT_FINGER_DOWN:
        case SDL_EVENT_FINGER_MOTION:
        case SDL_EVENT_FINGER_UP:
            return event.tfinger.windowID;
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
            return event.key.windowID;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            return event.button.windowID;
        case SDL_EVENT_MOUSE_MOTION:
            return event.motion.windowID;
        case SDL_EVENT_MOUSE_WHEEL:
            return event.wheel.windowID;
        case SDL_EVENT_TEXT_EDITING:
            return event.edit.windowID;
        case SDL_EVENT_TEXT_INPUT:
            return event.text.windowID;
        case SDL_EVENT_DROP_TEXT:
            return event.drop.windowID;
        case SDL_EVENT_WINDOW_HIDDEN:
        case SDL_EVENT_WINDOW_EXPOSED:
        case SDL_EVENT_WINDOW_MOVED:
        case SDL_EVENT_WINDOW_RESIZED:
        case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
        case SDL_EVENT_WINDOW_MINIMIZED:
        case SDL_EVENT_WINDOW_MAXIMIZED:
        case SDL_EVENT_WINDOW_RESTORED:
        case SDL_EVENT_WINDOW_MOUSE_ENTER:
        case SDL_EVENT_WINDOW_MOUSE_LEAVE:
        case SDL_EVENT_WINDOW_FOCUS_GAINED:
        case SDL_EVENT_WINDOW_FOCUS_LOST:
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        case SDL_EVENT_WINDOW_TAKE_FOCUS:
        case SDL_EVENT_WINDOW_HIT_TEST:
        case SDL_EVENT_WINDOW_ICCPROF_CHANGED:
        case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
            return event.window.windowID;
    }

    return std::nullopt;
}

float GetMouseX()
{
    float x;
    SDL_GetMouseState(&x, nullptr);
    return x;
}

float GetMouseY()
{
    float y;
    SDL_GetMouseState(nullptr, &y);
    return y;
}

Point GetMousePosition()
{
    float x, y;
    SDL_GetMouseState(&x, &y);

    return Point(static_cast<int>(x), static_cast<int>(y));
}

SDLW_NAMESPACE_END