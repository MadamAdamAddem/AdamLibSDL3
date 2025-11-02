#pragma once
#include <SDL3/SDL_render.h>

namespace AdamLib
{

  struct Texture
  {
    SDL_Texture* texture_;
    ~Texture();

    Texture(SDL_Texture* _texture);
  };

}