#pragma once

#include <SDL3/SDL_rect.h>

#include <cmath>

namespace sdlw
{
    struct Rect : public SDL_Rect
    {
        constexpr Rect() : SDL_Rect({0, 0, 0, 0}) {}
        constexpr Rect(const SDL_Rect& rect) : SDL_Rect({rect.x, rect.y, rect.w, rect.h}) {}
        constexpr Rect(int x, int y, int width, int height) : SDL_Rect({x, y, width, height}) {}

        constexpr int GetX() const { return x; }
        constexpr int GetY() const { return y; }
        constexpr int GetWidth() const { return w; }
        constexpr int GetHeight() const { return h; }

        void SetX(int value) { x = value; }
        void SetY(int value) { y = value; }
        void SetWidth(int value) { w = value; }
        void SetHeight(int value) { h = value; }

        constexpr bool operator==(const Rect& other)
        {
            return x == other.x && y == other.y && w == other.w && h == other.h;
        }
        
        constexpr bool operator!=(const Rect& other)
        {
            return (x != other.x) || (y != other.y) || (w != other.w) || (h != other.h);
        }
    };

    struct FRect : public SDL_FRect
    {
        static inline float ComparisonTolerance = 1e-6;

        constexpr FRect() : SDL_FRect({0, 0, 0, 0}) {}
        constexpr FRect(const SDL_FRect& rect) : SDL_FRect({rect.x, rect.y, rect.w, rect.h}) {}
        constexpr FRect(float x, float y, float width, float height) : SDL_FRect {x, y, width, height} {}

        constexpr float GetX() const { return x; }
        constexpr float GetY() const { return y; }
        constexpr float GetWidth() const { return w; }
        constexpr float GetHeight() const { return h; }

        void SetX(float value) { x = value; }
        void SetY(float value) { y = value; }
        void SetWidth(float value) { w = value; }
        void SetHeight(float value) { h = value; }

        bool operator==(const FRect& other)
        {
            return  std::abs(x - other.x) < ComparisonTolerance &&
                    std::abs(y - other.y) < ComparisonTolerance &&
                    std::abs(w - other.w) < ComparisonTolerance &&
                    std::abs(h - other.h) < ComparisonTolerance;
        }
        
        bool operator!=(const FRect& other)
        {
            return !(*this == other);
        }
    };
}