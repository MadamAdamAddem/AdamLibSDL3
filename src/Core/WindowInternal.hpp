#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <string>

namespace AdamLib
{


namespace GameWindow
{


  void createWindow(const std::string& _name = "AdamLib Lives On", int _w = 1280, int _h = 720);

}

}