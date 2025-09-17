#include "../include/Rendering.h"
#include "../include/Textures.h"

using namespace AdamLib;

namespace Renderer
{
  
  SDL_Renderer* renderer = nullptr;
  std::list<TextureResource*> render_order;

  double scale = 1;


void render_game()
{
  if(renderer == nullptr)
    return;

  for(auto texture : render_order)
    texture->render_instances();

}

void add_resource(TextureResource* res)
{
  for(auto it = render_order.begin(); it != render_order.end(); ++it)
  {
    if((*it)->getLayer() >= res->getLayer())
      render_order.insert(it, res);
  }

}

void delete_resource(TextureResource* res)
{
  render_order.remove(res);
}

}