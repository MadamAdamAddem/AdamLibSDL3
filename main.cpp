#include <iostream>

#include "src/include/Window.h"
#include "src/include/Rendering.h"
#include "src/include/Input.h"
#include "src/include/Texture.h"
#include "src/include/Node.h"
#include <SDL3_image/SDL_image.h>

#include "src/include/Signal.h"

uint64_t frame_time = 0;


//temporary, blow this bitch up eventually
void limitFPS()
{
  static const uint64_t goal_frame_time = (1000/60);

  frame_time = SDL_GetTicks() - frame_time;

  if(frame_time < goal_frame_time)
  {
    SDL_Delay(goal_frame_time - frame_time);
    std::cout << frame_time << "\n";
  }
}

using namespace AdamLib;

void print(double dt, Node* node)
{
  std::cout << node->name_ << " " << dt << std::endl;
}

int main(int argc, char** argv)
{

  SDL_Init(SDL_INIT_VIDEO);
  GameWindow& ref = GameWindow::getInstance();

  TextureInstance image("assets/square144.png");

  Script scrizzy{print};
  Script skizzy{print};

  Node niddy{"niddy",scrizzy};
  niddy.add_child(new Node("diddy", skizzy));


  int i=0;
  while(Input::processEvents())
  {
    //limitFPS();
    frame_time = SDL_GetTicks();

    niddy.process(++i);

    Renderer::render_all();
  }

  


  return 0;
}