#include <AdamLib/Core/Window.hpp>
#include <AdamLib/Core/Rendering.hpp>

#include <string>
#include <iostream>

using namespace AdamLib;


GameWindow::GameWindow(const std::string& title, int _w = 1280, int _h = 720) : 
  m_width(_w), m_height(_h),
  m_window(SDL_CreateWindow(title.c_str(), _w, _h, SDL_WINDOW_RESIZABLE), SDL_DestroyWindow)
{

  Renderer::initRenderer(m_window.get());
  if(m_window == nullptr)
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
  m_width = _w; m_height = _h;

  SDL_SetWindowSize(m_window.get(), _w, _h);
}
/*----------------------------------------------------------------------------------*/

