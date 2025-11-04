#pragma once
#include <AdamLib/Utilities/Math.hpp>
#include <AdamLib/Resources/Resource.hpp>


#include <memory>


namespace AdamLib
{

enum ScaleMode
{
  NEAREST = 0u,
  LINEAR_SCALING = 1u
};

enum FlipMode
{
  NO_FLIP = 0u,
  FLIP_HORIZONTAL = 1u,
  FLIP_VERTICAL = 2u
};

enum BlendMode
{
  BLEND_NONE = 0u,
  BLEND_BLEND = 1u,
  BLEND_ADD = 2u,
  BLEND_MOD = 4u,
  BEND_MUL = 8u,
  BLEND_BLEND_PREMULTIPLIED = 16u,
  BLEND_ADD_PREMULTIPLIED = 32u
};

class Texture;

class TextureResource : public Resource
{
  Texture* texture_;
public:

  TextureResource();
  ~TextureResource();

  virtual void initializeResource(const std::string& _path) override;

  inline Texture* getTexture() {return texture_;}


};

struct TextureInstance
{
  std::shared_ptr<TextureResource> m_texture;

  unsigned layer_;

  bool hidden_;

  Vec4f image_clip_{0,0,0,0};
  Vec4f render_destination_{0,0,0,0};

  Vec2 scale_{1,1};
  double angle_{0};

  FlipMode flip_{NO_FLIP};
  Vec4 colormod_{255,255,255,255};

  BlendMode blend_mode_{BLEND_NONE};


  void changeTexture(const std::string& _path, ScaleMode _scale_mode = NEAREST);
  void changeLayer(unsigned _layer);
  void setScale(Vec2 _scale);
  void setRenderCenter(Vec2 _center);

  /* Implement
  void setBlendMode(BlendMode);
  void setColorMod(SDL_Color);
  void setFlip(FlipMode);
  void setScaleMode(ScaleMode);
  */


  void removeFromRenderer();
  void addToRenderer();

  TextureInstance() = default;
  TextureInstance(const std::string& _path, ScaleMode _scale_mode = NEAREST);

  ~TextureInstance();

};


}