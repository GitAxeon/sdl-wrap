#pragma once

#include "../src/core/Macro.hpp"
#include "Point.hpp"

#include <SDL3/SDL_events.h>

#include <functional>
#include <optional>

namespace sdlw
{
    struct Event;
    
    using EventType = uint32_t;
    using WindowID = SDL_WindowID;
    using EventCallback = std::function<bool(Event&)>;
    using EventCategory = int;

    namespace Category
    {
        constexpr EventCategory Input = 1;
        constexpr EventCategory Mouse = 2;
        constexpr EventCategory Keyboard = 3;
        constexpr EventCategory Window = 4;
        constexpr EventCategory Display = 5;
    };

    struct Event
    {
        Event(SDL_Event& event) : SDL(event) { }
        bool HasCategory(EventCategory category) const { return Category & category; }

        SDL_Event& SDL;
        std::optional<WindowID> WindowID = std::nullopt;
        int Category = 0;
    };

    float GetMouseX();
    float GetMouseY();

    Point GetMousePosition();
}