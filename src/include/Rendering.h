#pragma once
#include <SDL3/SDL_render.h>



namespace AdamLib
{

class TextureInstance;

namespace Renderer
{




  SDL_Renderer* getRenderer();


  void render_all();
  void initRenderer(SDL_Window* window);

  void add_texture(TextureInstance* res);
  void remove_renderable(TextureInstance* res);


};


}