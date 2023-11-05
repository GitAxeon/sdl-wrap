#include "BasicClock.h"

#include "sdlw/SDLW.hpp"
#include <SDL3/SDL.h>

#include <filesystem>
#include <iostream>

int main(int argc, char* argv[])
{
    // Set current path to the one where the executable resides so that resources can be found
    std::filesystem::path workingDirectory(std::filesystem::path(argv[0]).parent_path());
    std::filesystem::current_path(workingDirectory);
    std::cout << "Set working directory to " << workingDirectory << std::endl;

    sdlw::Context ctx;

    sdlw::WindowInfo info("Testing", 640, 360);
    sdlw::Window window = ctx.CreateWindow(info);
    
    sdlw::Renderer renderer(window);
    sdlw::Texture texture(renderer, "resources/image.png");

    bool userInput = false;
    window.SetEventCallback([&](SDL_Event& event) -> bool
    {
        switch(event.type)
        {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                window.Close();
            break;
            case SDL_EVENT_KEY_DOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        window.Close();
                    break;
                    case SDLK_e:
                        userInput = true;
                    break;
                }
            break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                sdlw::Point mousePos = sdlw::GetMousePosition();
                userInput = true;
            break;
        }

        return true;
    });


    enum class HitStatus { Pending, Miss, Good, Great, Perfect };
    HitStatus currentHitStatus = HitStatus::Pending;
    std::string hitStatusString = "Pending";
    bool userAttemptedHit = false;
    float hitTimingDifferenceSeconds = 0;

    using namespace std::chrono_literals;

    constexpr std::chrono::milliseconds perfectWindow = 50ms;
    constexpr std::chrono::milliseconds greatWindow = 100ms;
    constexpr std::chrono::milliseconds goodWindow = 200ms;

    BasicClock clock;
    
    // Interval in seconds
    std::chrono::duration<float> interval(1);
    auto nextFlashTime = clock.Now() + interval;
    auto previousFlashTime = nextFlashTime;

    bool flash = false;
    int flashCount = 0;

    while (window.KeepOpen())
    {
        clock.Tick();
        ctx.PollEvents();

        // if(flash)
        // {
        //     flash = false;
        //     renderer.SetClearColor({0, 0, 0, 255});

        //     currentHitStatus = HitStatus::Pending;
        //     hitStatusString = "Pending";

        //     userAttemptedHit = false;
        //     hitTimingDifferenceSeconds = 0;
        // }

        // if(!userAttemptedHit && userInput)
        // {

        //     auto timingDifference = (clock.Now() - previousFlashTime);

        //     if (timingDifference < perfectWindow)
        //     {
        //         currentHitStatus = HitStatus::Perfect;
        //         hitStatusString = "Perfect";
        //     }
        //     else if (timingDifference < greatWindow)
        //     {
        //         currentHitStatus = HitStatus::Great;
        //         hitStatusString = "Great";
        //     }
        //     else if (timingDifference < goodWindow)
        //     {
        //         currentHitStatus = HitStatus::Good;
        //         hitStatusString = "Good";
        //     }
        //     else
        //     {
        //         currentHitStatus = HitStatus::Miss;
        //         hitStatusString = "Miss";
        //     }
            
        //     hitTimingDifferenceSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(timingDifference).count();
            
        //     userAttemptedHit = true;
        // }

        // userInput = false;

        // if ((nextFlashTime - clock.Now()).count() <= 0)
        // {
        //     flash = true;
        //     flashCount++;
            
        //     renderer.SetClearColor({255, 0, 255, 255});

        //     previousFlashTime = nextFlashTime;
        //     nextFlashTime += interval;
        // }

        // std::string titleText = std::to_string(clock.Elapsed());
        // titleText += " | " + std::to_string(flashCount);
        // titleText += " | " + hitStatusString + " diff: " + std::to_string(hitTimingDifferenceSeconds);
        // window.ChangeTitle(titleText);

        renderer.Clear();

        renderer.RenderTexture(texture);
        renderer.RenderTexture(texture, sdlw::FPoint(0, 0));
        renderer.RenderTexture(texture, sdlw::FPoint(128, 128));
        
        renderer.Present();
    }

    return 0;
}