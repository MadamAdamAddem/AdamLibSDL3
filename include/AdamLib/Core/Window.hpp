#pragma once
#include <memory>


namespace AdamLib
{

class Window;

//! Game Window Singleton
/*!
    For the most part you won't need to work with this
*/
class GameWindow
{

  GameWindow(const std::string& _title, int _w, int _h);
  GameWindow(const GameWindow&) = delete;
  GameWindow& operator=(const GameWindow&) = delete;


  std::unique_ptr<Window> window_;
  int width_, height_;

public:
  static GameWindow& getInstance();
  
  void resizeWindow(int _w, int _h);

};

}