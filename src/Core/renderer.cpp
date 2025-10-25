#include <AdamLib/Core/Rendering.hpp>
#include <AdamLib/Resources/Texture.hpp>

#include "RendererInternal.hpp"
#include "../Resources/ResourcesInternal.hpp"

#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <cassert>
#include <list>

using namespace AdamLib;


std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer{nullptr, SDL_DestroyRenderer};
std::list<TextureInstance*> render_order;
std::list<Renderer::SetOfPoints*> sets_of_points;

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

    SDL_Texture* texture = obj->m_texture->getTexture()->texture_;
    

    SDL_SetTextureColorMod(texture, obj->colormod_.x, obj->colormod_.y, obj->colormod_.w);
    SDL_SetTextureAlphaMod(texture, obj->colormod_.h);
    SDL_SetTextureBlendMode(texture, obj->blend_mode_);

    SDL_FRect clip = std::bit_cast<SDL_FRect>(obj->image_clip_);
    SDL_FRect destination = std::bit_cast<SDL_FRect>(obj->render_destination_);

    SDL_RenderTextureRotated(renderer.get(), texture, &clip, &destination, obj->angle_, NULL, static_cast<SDL_FlipMode>(obj->flip_));

  }

  SDL_SetRenderDrawColor(renderer.get(), CDC_R, CDC_G, CDC_B, CDC_A);
  //debug points
  for(auto& sop : sets_of_points)
  {
    SDL_RenderLines(renderer.get(), sop->points_.data(), sop->points_.size());
  }

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

void Renderer::addSetPoints(Renderer::SetOfPoints* _sop)
{
  sets_of_points.push_back(_sop);
}

void Renderer::removeSetPoints(Renderer::SetOfPoints* _sop)
{
  sets_of_points.remove(_sop);
}

SDL_Renderer* Renderer::getRenderer() {return renderer.get();}
