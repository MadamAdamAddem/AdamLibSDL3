#include <AdamLib/Core/Rendering.hpp>
#include <AdamLib/Resources/Texture.hpp>

#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <cassert>
#include <list>

using namespace AdamLib;


std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer{nullptr, SDL_DestroyRenderer};
std::list<TextureInstance*> render_order;

#ifdef DRAW_COLLISION
std::list<Renderer::SetOfPoints*> sets_of_points;
#endif

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

  SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 0);
  SDL_RenderClear(renderer.get());

  //textures
  for(auto& obj : render_order)
  {
    if(obj->hidden_)
      continue;
      
    if(obj->m_texture == nullptr)
      continue;

    SDL_Texture* texture = obj->m_texture->getTexture();
    

    SDL_SetTextureColorMod(texture, obj->colormod_.r, obj->colormod_.g, obj->colormod_.b);
    SDL_SetTextureAlphaMod(texture, obj->colormod_.a);
    SDL_SetTextureBlendMode(texture, obj->blend_mode_);

    SDL_RenderTextureRotated(renderer.get(), texture, &obj->image_clip_, &obj->render_destination_, obj->angle_, NULL, obj->flip_);

  }


  #ifdef DRAW_COLLISION
  //debug points
  for(auto& sop : sets_of_points)
  {
    SDL_SetRenderDrawColor(renderer.get(), sop->draw_color_.r, sop->draw_color_.g, sop->draw_color_.b, sop->draw_color_.a);
    SDL_RenderLines(renderer.get(), sop->points_.data(), sop->points_.size());
  }
  #endif

  SDL_RenderPresent(renderer.get());
}

void Renderer::addTexture(TextureInstance* res)
{
  assert(res != nullptr);
  
  for(auto it = render_order.begin(); it != render_order.end(); ++it)
  {
    if(*it == res)
      return;
    
    if((*it)->layer_ < res->layer_)
    {
      render_order.insert(it, res);
      return;
    }
      
  }

  render_order.push_back(res);
}

void Renderer::removeRenderable(TextureInstance* res)
{
  render_order.remove(res);
}

SDL_Renderer* Renderer::getRenderer()
{
  return renderer.get();
}

#ifdef  DRAW_COLLISION
void Renderer::addSetPoints(Renderer::SetOfPoints* _sop)
{
  sets_of_points.push_back(_sop);
}

void Renderer::removeSetPoints(Renderer::SetOfPoints* _sop)
{
  sets_of_points.remove(_sop);
}
#endif
