#pragma once
#include "Resource.h"
#include <memory>
#include <SDL3/SDL_render.h>


namespace AdamLib
{

enum ScaleMode
{
  NEAREST = SDL_SCALEMODE_NEAREST,
  LINEAR_SCALING = SDL_SCALEMODE_LINEAR
};


class TextureResource : public Resource
{
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_texture; 

public:

  TextureResource();
  ~TextureResource() = default;

  virtual void createResource(const std::string& path) override;

  inline virtual SDL_Texture* getTexture() {return m_texture.get();}


};

struct TextureInstance
{
  std::shared_ptr<TextureResource> m_texture;

  unsigned layer = 1;

  SDL_FRect image_clip{0,0,0,0};
  SDL_FRect render_destination{0,0,0,0};

  double scale{1};
  double angle{0};

  SDL_FPoint center{0,0};
  SDL_FlipMode flip{SDL_FLIP_NONE};
  SDL_Color color_mod{0,0,0,0};

  bool hidden{false};

  TextureInstance() = default;
  TextureInstance(const std::string& path, ScaleMode scale_mode = NEAREST);

};


}