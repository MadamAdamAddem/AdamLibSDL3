#pragma once
#include <SDL3/SDL.h>
#include <AdamLib/Defines.hpp>
#include <AdamLib/Math.hpp>
#include <SDL3/SDL_rect.h>
#include <vector>

namespace AdamLib
{


namespace Renderer
{


  #ifdef DRAW_COLLISION
  struct SetOfPoints
  {
    std::vector<SDL_FPoint>points_;
  };


  void addSetPoints(SetOfPoints* _sop);
  void removeSetPoints(SetOfPoints* _sop);
  #endif

  //! Do not call, internal only
  void initRenderer(SDL_Window* _window);

  SDL_Renderer* getRenderer();

}

}