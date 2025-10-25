#pragma once
#include <SDL3/SDL.h>

namespace AdamLib
{


struct Window
{
  SDL_Window* window_;

  ~Window()
  {
    SDL_DestroyWindow(window_);
  }

  Window(SDL_Window* _window) : window_(_window) {}

  inline operator SDL_Window*() const
  {
    return window_;
  }

};


}