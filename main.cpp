#include <iostream>
#include "src/include/Window.h"
#include "src/include/Rendering.h"
#include "src/include/Input.h"
#include <SDL3_image/SDL_image.h>




int main(int argc, char** argv)
{
  using namespace AdamLib;

  SDL_Init(SDL_INIT_VIDEO);
  GameWindow& ref = GameWindow::getInstance();
  Renderer& renderer = Renderer::getInstance();

  Renderable image("assets/square144.png");

  SDL_Event e;
  bool keep_going = true;

  while(Input::processEvents())
  {


    renderer.render_all();

  }



  std::cout << SDL_GetError() << std::endl;
  return 0;
}