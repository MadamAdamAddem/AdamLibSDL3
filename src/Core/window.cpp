#include "WindowInternal.hpp"
#include "RendererInternal.hpp"
#include <AdamLib/Core/Window.hpp>

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <memory>
#include <iostream>

using namespace AdamLib;


std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window{nullptr, SDL_DestroyWindow};

void GameWindow::createWindow(const std::string& _name, int _w, int _h)
{
  static bool hasRan = false;
  if(hasRan) return;

  SDL_Window* newin;
  SDL_Renderer* newren;

  if(!SDL_CreateWindowAndRenderer(_name.c_str(), _w, _h, SDL_WINDOW_RESIZABLE, &newin, &newren))
  {
    std::cout << SDL_GetError() << std::endl;
    exit(1);
  }

  window.reset(newin);
  Renderer::initRenderer(newren);
  hasRan = true;
}


/*----------------------------------------------------------------------------------*/

void GameWindow::setWindowSettings(const WindowSettings &_settings)
{
  setWindowResizeable(_settings.resizeability_);
  setWindowState(_settings.state_);
  setWindowMode(_settings.mode_);
  resizeWindow(_settings.dimensions_);

  if(!_settings.title_.empty())
    renameWindow(_settings.title_);
}


void GameWindow::setWindowMode(WindowMode _mode)
{
  switch(_mode)
  {
    case WindowMode::BorderedWindow:
      SDL_SetWindowFullscreen(window.get(), false);
      SDL_SetWindowBordered(window.get(), true);
      break;

    case WindowMode::BorderlessWindow:
      SDL_SetWindowFullscreen(window.get(), false);
      SDL_SetWindowBordered(window.get(), false);
      break;

    case WindowMode::BorderlessFullscreen:
      SDL_SetWindowFullscreen(window.get(), true);
      break;


    case WindowMode::ExclusiveFullscreen:
    {
      auto displaymodes = SDL_GetFullscreenDisplayModes(SDL_GetPrimaryDisplay(), NULL);
      SDL_SetWindowFullscreenMode(window.get(), displaymodes !=NULL ? displaymodes[0] : NULL);
    }
      break;

    case WindowMode::RetainCurrent:
    default:
      break;
  }

  SDL_SyncWindow(window.get());
}

void GameWindow::setWindowState(WindowState _state)
{

  switch(_state)
  {
    case WindowState::Standard:
      SDL_RestoreWindow(window.get());
      break;

    case WindowState::Minimized:
      SDL_MinimizeWindow(window.get());
      break;

    case WindowState::Maximized:
      SDL_MaximizeWindow(window.get());
      break;

    case WindowState::RetainCurrent:
    default:
      break;
  }

  SDL_SyncWindow(window.get());
}

void GameWindow::setWindowResizeable(WindowResizeability _resizeability)
{
  switch(_resizeability)
  {
    case WindowResizeability::NonUserResizeable:
      SDL_SetWindowResizable(window.get(), false);
      break;
    case WindowResizeability::UserResizeable:
      SDL_SetWindowResizable(window.get(), true);
      break;
    case WindowResizeability::RetainCurrent:
    default:
      break;
  }
  SDL_SyncWindow(window.get());
}



void GameWindow::resizeWindow(const int _w, const int _h)
{
  if(!SDL_SetWindowSize(window.get(), _w, _h))
  {
    std::cout << SDL_GetError() << std::endl;
    exit(1);
  }
}

void GameWindow::resizeWindow(const Vec2i& _dimensions)
{
  if(!SDL_SetWindowSize(window.get(), _dimensions.x, _dimensions.y))
  {
    std::cout << SDL_GetError() << std::endl;
    exit(1);
  }
}

void GameWindow::renameWindow(const std::string& _new_name)
{
  SDL_SetWindowTitle(window.get(), _new_name.c_str());
}


Vec2i GameWindow::getWindowDimensions()
{
  int w, h;
  SDL_GetWindowSize(window.get(), &w, &h);
  return Vec2i(w, h);
  
}

/*----------------------------------------------------------------------------------*/

