#include "../Core/RendererInternal.hpp"
#include "ResourcesInternal.hpp"

#include <AdamLib/Resources/Texture.hpp>
#include <AdamLib/Resources/ResManager.hpp>
#include <AdamLib/Core/Rendering.hpp>

#include <SDL3_image/SDL_image.h>

using namespace AdamLib;





TextureResource::TextureResource() : texture_(nullptr)
{

}

TextureResource::~TextureResource()
{
  delete texture_;
}


void TextureResource::initializeResource(const std::string& _path)
{
  texture_ = new Texture(IMG_LoadTexture(Renderer::getRenderer(), _path.c_str()));
}

/*---------------------------------------------------------------------------------------------------------------*/


TextureInstance::TextureInstance(const std::string& _path, ScaleMode _scale_mode) :  
m_texture(std::static_pointer_cast<TextureResource>(ResManager::requestResource(_path, ResManager::Texture)))
{
  SDL_SetTextureScaleMode(m_texture->getTexture()->texture_, static_cast<SDL_ScaleMode>(_scale_mode));

  float w, h;
  SDL_GetTextureSize(m_texture->getTexture()->texture_, &w, &h);

  image_clip_.w = w;
  image_clip_.h = h;
  render_destination_.w = w;
  render_destination_.h = h;

  hidden_ = false;
  layer_ = 1;
}

void TextureInstance::changeTexture(const std::string& _path, ScaleMode _scale_mode)
{
  m_texture.reset();
  m_texture = std::static_pointer_cast<TextureResource>(ResManager::requestResource(_path, ResManager::Texture));
  SDL_SetTextureScaleMode(m_texture->getTexture()->texture_, static_cast<SDL_ScaleMode>(_scale_mode));

  float w, h;
  SDL_GetTextureSize(m_texture->getTexture()->texture_, &w, &h);

  image_clip_.w = w;
  image_clip_.h = h;
  render_destination_.w = w;
  render_destination_.h = h;
}

void TextureInstance::removeFromRenderer()
{
  Renderer::removeRenderable(this);
}

void TextureInstance::addToRenderer()
{
  Renderer::addTexture(this);
}

void TextureInstance::changeLayer(unsigned _layer)
{
  layer_ = _layer;
  removeFromRenderer();
  addToRenderer();
}

void TextureInstance::setScale(Vec2 _scale)
{
  render_destination_.w = image_clip_.w * _scale.x;
  render_destination_.h = image_clip_.h * _scale.y;
}

TextureInstance::~TextureInstance()
{
  Renderer::removeRenderable(this);
  m_texture.reset();
}

void TextureInstance::setRenderCenter(Vec2 _center)
{
  render_destination_.x = _center.x - render_destination_.w/2;
  render_destination_.y = _center.y - render_destination_.h/2;
}

/*---------------------------------------------------------------------------------------------------------------*/

Texture::~Texture()
{
  SDL_DestroyTexture(texture_);
}

Texture::Texture(SDL_Texture* _texture) : texture_(_texture) {}
