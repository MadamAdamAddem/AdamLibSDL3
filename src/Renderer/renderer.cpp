#include "../include/Rendering.h"
#include "../include/Window.h"
#include "../include/ResManager.h"
#include "../include/Texture.h"

#include <iostream>
#include <list>

using namespace AdamLib;


std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer{nullptr, SDL_DestroyRenderer};
std::list<TextureInstance*> render_order;


/*---------------------------------------------------------------------------------------------------------------*/

void Renderer::initRenderer(SDL_Window* window)
{
  renderer.reset(SDL_CreateRenderer(window, NULL));
  SDL_SetRenderLogicalPresentation(renderer.get(), 1280, 720, SDL_LOGICAL_PRESENTATION_STRETCH);
  SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
}

void Renderer::render_all()
{
  if(renderer == nullptr)
    return;

  for(auto obj : render_order)
  {
    if(obj->hidden || obj->m_texture == nullptr)
    return;

    SDL_Texture* texture = obj->m_texture->getTexture();
    
  if(obj->color_mod.a != 0)
    SDL_SetTextureColorMod(texture, obj->color_mod.r, obj->color_mod.g, obj->color_mod.b);

  SDL_RenderTextureRotated(renderer.get(), texture, &obj->image_clip, &obj->render_destination, obj->angle, &obj->center, obj->flip);
  SDL_SetTextureColorMod(texture, 0xFF, 0xFF, 0xFF);
  }

  SDL_RenderPresent(renderer.get());
}

void Renderer::add_texture(TextureInstance* res)
{
  for(auto it = render_order.begin(); it != render_order.end(); ++it)
  {
    if((*it)->layer >= res->layer)
    {
      render_order.insert(it, res);
      return;
    }
      
  }
  render_order.push_back(res);
}

void Renderer::remove_renderable(TextureInstance* res)
{
  render_order.remove(res);
}

SDL_Renderer* Renderer::getRenderer()
{
  return renderer.get();
}