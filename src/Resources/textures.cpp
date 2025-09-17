#include "../include/Rendering.h"
#include "../include/Textures.h"

using namespace AdamLib;


TextureResource::TextureResource(SDL_Texture* _texture, int _w, int _h) : m_texture(_texture), width(_w), height(_h)
{

}

int TextureResource::getLayer() {return layer;}

void TextureResource::render_instances()
{
  if(m_texture == nullptr)
    return;
  
  for(auto& data : render_details)
  {
    if(data.image_clip.w == 0 && data.image_clip.h == 0)
    {
      data.image_clip.w = width;
      data.image_clip.h = height;
    }

    if(data.color_mod.a != 0)
      SDL_SetTextureColorMod(m_texture, data.color_mod.r, data.color_mod.g, data.color_mod.b);

    SDL_RenderTextureRotated(Renderer::renderer, m_texture, &data.image_clip, &data.render_destination, data.angle, &data.center, data.flip);
    SDL_SetTextureColorMod(m_texture, 0, 0, 0);
  }
}