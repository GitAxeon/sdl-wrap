#pragma once
#include <chrono>

class BasicClock
{
public:
    BasicClock()
    {
        m_Started = std::chrono::high_resolution_clock::now();
        m_FrameStart = m_Started;
        m_PreviousFrame = m_Started;
    }

    void Tick()
    {
        m_PreviousFrame = m_FrameStart;
        m_FrameStart = std::chrono::high_resolution_clock::now();
    }

    // Return seconds between the previous frame and the start of current frame
    float DeltaSeconds()
    {
        auto duration = std::chrono::duration<float>(m_FrameStart - m_PreviousFrame).count();

        return (duration);
    }

    // Return seconds elapsed since the creation of the object
    float Elapsed()
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = (now - m_Started);
        return (duration.count());
    }

    // Return the time_point of the current frame start
    std::chrono::high_resolution_clock::time_point FrameStart()
    {
        return (m_FrameStart);
    }

    // Return the current time as a time_point
    std::chrono::high_resolution_clock::time_point Now()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return (now);
    }

    float SecondsSince(std::chrono::high_resolution_clock::time_point tp)
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = (now - tp);
        return (duration.count());
    }
    
private:
    std::chrono::high_resolution_clock::time_point m_Started;
    std::chrono::high_resolution_clock::time_point m_FrameStart;
    std::chrono::high_resolution_clock::time_point m_PreviousFrame;
};