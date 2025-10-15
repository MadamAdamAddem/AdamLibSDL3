#pragma once
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <vector>


namespace AdamLib
{

class TextureInstance;

namespace Renderer
{

  struct SetOfPoints
  {
    SDL_Color draw_color_{0,255,255,255};
    std::vector<SDL_FPoint> points_;
  };


  SDL_Renderer* getRenderer();


  void render_all();
  void initRenderer(SDL_Window* _window);

  void addTexture(TextureInstance* _res);
  void removeRenderable(TextureInstance* _res);

  void addSetPoints(SetOfPoints* _sop);
  void removeSetPoints(SetOfPoints* _sop);

};


}