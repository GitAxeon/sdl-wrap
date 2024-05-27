#pragma once

#include "../src/core/Macro.hpp"
#include "Point.hpp"

#include <SDL3/SDL_events.h>
#include <functional>

namespace sdlw
{
    using EventType = uint32_t;
    using WindowID = SDL_WindowID;
    using EventCallback = std::function<bool(SDL_Event &)>;

    float GetMouseX();
    float GetMouseY();

    Point GetMousePosition();
}