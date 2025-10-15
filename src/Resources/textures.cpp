#include <AdamLib/Resources/Texture.hpp>
#include <AdamLib/Resources/ResManager.hpp>
#include <AdamLib/Core/Rendering.hpp>

#include <SDL3_image/SDL_image.h>

using namespace AdamLib;


TextureResource::TextureResource() : texture_(nullptr, SDL_DestroyTexture)
{

}


void TextureResource::createResource(const std::string& _path)
{
  texture_.reset(IMG_LoadTexture(Renderer::getRenderer(), _path.c_str()));
}

/*---------------------------------------------------------------------------------------------------------------*/


TextureInstance::TextureInstance(const std::string& _path, ScaleMode _scale_mode) :  m_texture(ResManager::requestResource<TextureResource>(_path))
{
  SDL_SetTextureScaleMode(m_texture->getTexture(), (SDL_ScaleMode)_scale_mode);
  SDL_GetTextureSize(m_texture->getTexture(), &image_clip_.w, &image_clip_.h);
  render_destination_.w = image_clip_.w;
  render_destination_.h = image_clip_.h;
  hidden_ = false;
  layer_ = 1;
  Renderer::addTexture(this);
}

void TextureInstance::changeTexture(const std::string& _path, ScaleMode _scale_mode)
{
  m_texture.reset();
  m_texture = (ResManager::requestResource<TextureResource>(_path));
  SDL_SetTextureScaleMode(m_texture->getTexture(), (SDL_ScaleMode)_scale_mode);
  SDL_GetTextureSize(m_texture->getTexture(), &image_clip_.w, &image_clip_.h);
  render_destination_.w = image_clip_.w;
  render_destination_.h = image_clip_.h;
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
