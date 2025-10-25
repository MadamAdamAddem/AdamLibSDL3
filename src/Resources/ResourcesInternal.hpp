#pragma once
#include <SDL3/SDL_render.h>

namespace AdamLib
{


struct Texture
{
  SDL_Texture* texture_;

  ~Texture()
  {
    SDL_DestroyTexture(texture_);
  }

  Texture(SDL_Texture* _texture) : texture_(_texture) {}

  inline operator SDL_Texture*() const
  {
    return texture_;
  }

};


}