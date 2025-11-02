#pragma once
#include <AdamLib/Math.hpp>
#include <string>

namespace AdamLib
{

class Window;

//! Game Window Management
/*!
*/
namespace GameWindow
{
  enum class WindowMode
  {
    RetainCurrent,
    BorderedWindow,
    BorderlessWindow,
    ExclusiveFullscreen,
    BorderlessFullscreen
  };

  enum class WindowState
  {
    RetainCurrent,
    Minimized,
    Standard,
    Maximized
  };

  enum class WindowResizeability
  {
    RetainCurrent,
    NonUserResizeable,
    UserResizeable
  };

  struct WindowSettings
  {
    Vec2i dimensions_;
    Vec2i position_;
    std::string title_;

    WindowMode mode_{WindowMode::RetainCurrent};
    WindowState state_{WindowState::RetainCurrent};
    WindowResizeability resizeability_{WindowResizeability::RetainCurrent};
  };

  /*
    SDL_GetWindowSize
    SDL_MaximizeWindow
    SDL_MinimizeWindow
    SDL_RestoreWindow
    SDL_SetWindowBordered
    SDL_SetWindowFullscreen
    SDL_SetWindowFullscreenMode
    SDL_SetWindowPosition
    SDL_SetWindowResizeable
    SDL_SetWindowTitle
  */

  void setWindowSettings(const WindowSettings& _settings);

  void setWindowMode(WindowMode _mode);
  void setWindowState(WindowState _state);
  void setWindowResizeable(WindowResizeability _resizeability);

  void resizeWindow(const int _w, const int _h);
  void resizeWindow(const Vec2i& _dimensions);
  void renameWindow(const std::string& _new_name);

  Vec2i getWindowDimensions();



}

}