#pragma once

#include "../include/sdlw/Event.hpp"

SDLW_NAMESPACE_BEGIN

enum class EventScope { Directed, General };

EventScope GetEventScope(EventType type);
WindowID GetWindowID(const SDL_Event& event);

SDLW_NAMESPACE_END