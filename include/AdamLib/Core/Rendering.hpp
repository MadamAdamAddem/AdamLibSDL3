#pragma once


#include <AdamLib/Defines.hpp>

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#ifdef DRAW_COLLISION
#include <vector>
#endif

namespace AdamLib
{

class TextureInstance;

namespace Renderer
{

  #ifdef DRAW_COLLISION
  struct SetOfPoints
  {
    SDL_Color draw_color_{0,255,255,255};
    std::vector<SDL_FPoint> points_;
  };


  void addSetPoints(SetOfPoints* _sop);
  void removeSetPoints(SetOfPoints* _sop);
  #endif


  SDL_Renderer* getRenderer();


  //! I wonder what this one does
  void render_all();

  //! Do not call, internal only
  void initRenderer(SDL_Window* _window);

  //! Adds given instance to render queue, must be removed manually
  void addTexture(TextureInstance* _res);

  //! Removes given instance from render queue.
  void removeRenderable(TextureInstance* _res);


};


}