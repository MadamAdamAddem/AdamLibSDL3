#pragma once
#include <SDL3/SDL.h>
#include <AdamLib/Defines.hpp>
#include <AdamLib/Utilities/Math.hpp>
#include <SDL3/SDL_rect.h>
#include <vector>

namespace AdamLib
{


namespace Renderer
{


  struct SetOfPoints
  {
    std::vector<SDL_FPoint> points_;
  };


  void addSetPoints(SetOfPoints* _sop);
  void removeSetPoints(SetOfPoints* _sop);

  //! If called more than once it just kinda doesn't do anything
  void initRenderer(SDL_Renderer* _window);

  SDL_Renderer* getRenderer();

}

}