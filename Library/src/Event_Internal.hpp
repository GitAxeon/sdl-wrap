#pragma once

#include "../include/sdlw/Event.hpp"

SDLW_NAMESPACE_BEGIN

std::optional<WindowID> GetWindowID(const SDL_Event& event);

SDLW_NAMESPACE_END