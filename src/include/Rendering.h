#pragma once
#include <SDL3/SDL_render.h>
#include <list>


namespace AdamLib
{

class TextureResource;

namespace Renderer
{

  extern SDL_Renderer* renderer;
  extern std::list<TextureResource*> render_order;

  extern double scale;

  void render_game();

  void add_resource(TextureResource* res);

  void delete_resource(TextureResource* res);

  
};



}
