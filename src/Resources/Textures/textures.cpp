#include "../../include/Texture.h"
#include "../../include/Rendering.h"
#include "../../include/ResManager.h"
#include <SDL3_image/SDL_image.h>

using namespace AdamLib;


TextureResource::TextureResource() : m_texture(nullptr, SDL_DestroyTexture)
{

}


void TextureResource::createResource(const std::string& path)
{
  m_texture.release();
  m_texture.reset(IMG_LoadTexture(Renderer::getRenderer(), path.c_str()));
}

/*---------------------------------------------------------------------------------------------------------------*/


TextureInstance::TextureInstance(const std::string& path, ScaleMode scale_mode) :  m_texture(ResManager::requestResource<TextureResource>(path))
{
  SDL_SetTextureScaleMode(m_texture->getTexture(), (SDL_ScaleMode)scale_mode);
  SDL_GetTextureSize(m_texture->getTexture(), &image_clip.w, &image_clip.h);
  render_destination.w = image_clip.w;
  render_destination.h = image_clip.h;
  Renderer::add_texture(this);
}
