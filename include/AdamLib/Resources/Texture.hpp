#pragma once
#include "AdamLib/Math.hpp"
#include <AdamLib/Resources/Resource.hpp>
#include <SDL3/SDL_blendmode.h>
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
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture_; 

public:

  TextureResource();
  ~TextureResource() = default;

  virtual void createResource(const std::string& _path) override;

  inline virtual SDL_Texture* getTexture() {return texture_.get();}


};

struct TextureInstance
{
  std::shared_ptr<TextureResource> m_texture;

  unsigned layer_;

  bool hidden_;

  SDL_FRect image_clip_{0,0,0,0};
  SDL_FRect render_destination_{0,0,0,0};

  SDL_FRect scale_{1,1};
  double angle_{0};

  SDL_FlipMode flip_{SDL_FLIP_NONE};
  SDL_Color colormod_{255,255,255,255};

  SDL_BlendMode blend_mode_{SDL_BLENDMODE_NONE};


  void changeTexture(const std::string& _path, ScaleMode _scale_mode = NEAREST);
  void changeLayer(unsigned _layer);
  void setScale(Vec2 _scale);
  void setRenderCenter(Vec2 _center);

  void removeFromRenderer();
  void addToRenderer();

  TextureInstance() = default;
  TextureInstance(const std::string& _path, ScaleMode _scale_mode = NEAREST);

  ~TextureInstance();

};


}