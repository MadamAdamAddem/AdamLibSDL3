#pragma once
#include <SDL3/SDL.h>
#include <memory>


namespace AdamLib
{

//! Game Window Singleton
/*!
    For the most part you won't need to work with this
*/
class GameWindow
{

  GameWindow(const std::string& _title, int _w, int _h);
  GameWindow(const GameWindow&) = delete;
  GameWindow& operator=(const GameWindow&) = delete;


  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;
  int width_, height_;

public:
  static GameWindow& getInstance();
  
  void resizeWindow(int _w, int _h);

};

}