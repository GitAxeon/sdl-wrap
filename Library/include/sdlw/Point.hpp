#pragma once

#include <SDL3/SDL_rect.h>

#include <cmath>

namespace sdlw
{
    struct Point : public SDL_Point
    {
        constexpr Point() : SDL_Point({0, 0}) {}
        constexpr Point(const Point& other) : SDL_Point({other.x, other.y}) {}
        constexpr Point(int x, int y) : SDL_Point({x, y}) {}
        constexpr int GetX() const { return x; }
        constexpr int GetY() const { return y; }
        void SetX(int value) { x = value; }
        void SetY(int value) { y = value; }
        constexpr Point operator+(const Point& other) const { return Point(x + other.x, y + other.y); }
        constexpr Point operator-(const Point& other) const { return Point(x - other.x, y - other.y); }
        constexpr Point operator/(int scalar) const { return Point(x / scalar, y / scalar); }
        constexpr Point operator*(int scalar) const { return Point(x * scalar, y * scalar); }

        constexpr Point& operator+=(const Point &other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        constexpr Point& operator-=(const Point &other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        constexpr Point& operator/=(int scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        constexpr Point& operator*=(int scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this; 
        }

        constexpr bool operator==(const Point& other) const { return x == other.x && y == other.y; }
        constexpr bool operator!=(const Point& other) const { return (x != other.x) || (y != other.y); }
    };

    struct FPoint : public SDL_FPoint
    {
        static constexpr float ComparisonTolerance = 1e-6;

        constexpr FPoint() : SDL_FPoint({0, 0}) {}
        constexpr FPoint(const FPoint& other) : SDL_FPoint({other.x, other.y}) {}
        constexpr FPoint(float x, float y) : SDL_FPoint({x, y}) {}
        constexpr float GetX() const { return x; }
        constexpr float GetY() const { return y; }
        void SetX(float value) { x = value; }
        void SetY(float value) { y = value; }
        constexpr FPoint operator+(const FPoint& other) const { return FPoint(x + other.x, y + other.y); }
        constexpr FPoint operator-(const FPoint& other) const { return FPoint(x - other.x, y - other.y); }
        constexpr FPoint operator/(float scalar) const { return FPoint(x / scalar, y / scalar); }
        constexpr FPoint operator*(float scalar) const { return FPoint(x * scalar, y * scalar); }

        constexpr FPoint& operator+=(const FPoint &other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        constexpr FPoint& operator-=(const FPoint &other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        constexpr FPoint& operator/=(float scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        constexpr FPoint& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this; 
        }

        bool operator==(const FPoint& other) const
        {
            return std::abs(x - other.x) < ComparisonTolerance && std::abs(y - other.y) < ComparisonTolerance;
        }

        bool operator!=(const FPoint& other) const
        {
            return !(*this == other);
        }
    };
}