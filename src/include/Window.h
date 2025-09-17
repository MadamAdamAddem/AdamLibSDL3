#pragma once
#include <SDL3/SDL.h>
#include <memory>

class GameWindow
{
  GameWindow(const std::string& title, int _w, int _h);
  GameWindow(const GameWindow&) = delete;
  GameWindow& operator=(const GameWindow&) = delete;


  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
  int screenW, screenH;
  float globalRenderScale = 1.0f;  

public:
  static GameWindow& getInstance();


  void resizeWindow(int _w, int _h);

  inline const SDL_Window& getWindow() const {return *window;}
};