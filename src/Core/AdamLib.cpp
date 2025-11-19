#include "WindowInternal.hpp"
#include <AdamLib/Core/AdamLib.hpp>
#include <AdamLib/Core/Window.hpp>
#include <AdamLib/Nodes/Node.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_timer.h>


uint64_t last_tick = 0;
uint64_t current_tick = 0;

double AdamLib::update()
{
  last_tick = current_tick;
  current_tick = SDL_GetTicks();
  return (current_tick - last_tick) / 1000.0;
}

uint64_t frame_time = 0;
// //temporary, blow this bitch up eventually
// void AdamLib::limitFPS(int _fps)
// {
//   static const uint64_t goal_frame_time = (1000/_fps);
//
//   frame_time = SDL_GetTicks() - frame_time;
//
//   if(frame_time < goal_frame_time)
//   {
//     SDL_Delay(goal_frame_time - frame_time);
//   }
//
//   frame_time = SDL_GetTicks();
// }


void AdamLib::initialize()
{
  static bool initialized = false;
  if(initialized) return;

  SDL_Init(SDL_INIT_VIDEO);
  GameWindow::createWindow("AdamLib is dead! Long Live AdamLibSDL3 Port!");
  initialized = true;
}

void AdamLib::quit()
{
  SDL_Quit();
}