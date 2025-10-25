#include "WindowInternal.hpp"
#include "RendererInternal.hpp"
#include <AdamLib/Core/Window.hpp>

#include <string>
#include <iostream>

using namespace AdamLib;


GameWindow::GameWindow(const std::string& title, int _w = 1280, int _h = 720) : 
  width_(_w), height_(_h),
  window_(new Window(SDL_CreateWindow(title.c_str(), _w, _h, SDL_WINDOW_RESIZABLE)))
{

  Renderer::initRenderer(window_.get()->window_);
  if(window_ == nullptr)
  {
    std::cout << SDL_GetError() << std::endl;
    exit(1);
  }

}

GameWindow& GameWindow::getInstance()
{
  static GameWindow single("SDL3 Port!");
  return single;
}


void GameWindow::resizeWindow(int _w, int _h)
{
  width_ = _w; height_ = _h;

  SDL_SetWindowSize(window_.get()->window_, _w, _h);
}
/*----------------------------------------------------------------------------------*/

