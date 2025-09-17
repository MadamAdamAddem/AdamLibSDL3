#pragma once
#include <SDL3/SDL.h>

class GameWindow
{
public:
  GameWindow();
  GameWindow(int SCREENW, int SCREENH);
  ~GameWindow();


  void initAll();
  void resizeWindow(int newW, int newH);
  void render() const;

  inline const SDL_Renderer& getRenderer() const {return *renderer;}
  inline const SDL_Window& getWindow() const {return *window;}

private:

  SDL_Renderer* ainitRenderer(bool vsync = false);
  SDL_Window* ainitWindow();

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;


  int screenW, screenH;

  float globalRenderScale = 1.0f;  
};