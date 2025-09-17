#pragma once
#include <vector>
#include <SDL3/SDL.h>


namespace AdamLib
{


  struct TextureInstance
  {
    SDL_FRect image_clip{0,0,0,0};
    SDL_FRect render_destination{0,0,0,0};

    double scale{1};
    double angle{0};

    SDL_FPoint center{0,0};
    SDL_FlipMode flip{SDL_FLIP_NONE};
    SDL_Color color_mod{0,0,0,0};



  };



  class TextureResource
  {
    TextureResource(SDL_Texture* _texture, int _w, int _h);

    SDL_Texture* m_texture = nullptr;
    unsigned width = 0;
    unsigned height = 0;
    unsigned layer = 1;

    std::vector<TextureInstance> render_details;

  public:

    int getLayer();
    void render_instances();


  };




}