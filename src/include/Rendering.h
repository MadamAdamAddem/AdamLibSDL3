#pragma once
#include <SDL3/SDL_render.h>
#include <memory>
#include <list>


enum ScaleMode
{
  NEAREST = SDL_SCALEMODE_NEAREST,
  LINEAR_SCALING = SDL_SCALEMODE_LINEAR
};

namespace AdamLib
{

class Texture;

class Renderable
{

  std::shared_ptr<Texture> m_texture;

protected:

  unsigned layer = 1;

  SDL_FRect image_clip{0,0,0,0};
  SDL_FRect render_destination{0,0,0,0};

  double scale{1};
  double angle{0};

  SDL_FPoint center{0,0};
  SDL_FlipMode flip{SDL_FLIP_NONE};
  SDL_Color color_mod{0,0,0,0};

  bool hidden{false};

public:
  Renderable() = default;
  Renderable(const std::string& path, ScaleMode scale_mode = NEAREST);

  virtual void render(SDL_Renderer* renderer);
  inline unsigned getLayer() {return layer;}


};

class Renderer
{
  friend class GameWindow;
  Renderer(SDL_Window* window);
  Renderer(const Renderer&) = delete;
  Renderer& operator=(const Renderer&) = delete;

  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
  std::list<Renderable*> render_order;


public:

  //do not call this unless GameWindow has already been created, or you have set up your own window for some reason
  static Renderer& getInstance(SDL_Window* ignore_this_pls = nullptr);
  static SDL_Renderer* getRenderer();

  void render_all();

  void add_renderable(Renderable* res);
  void remove_renderable(Renderable* res);


};


}