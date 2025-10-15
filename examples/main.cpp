#include <iostream>
#include <SDL3_image/SDL_image.h>

#include <AdamLib/Core/Window.hpp>
#include <AdamLib/Core/Rendering.hpp>
#include <AdamLib/Input.hpp>
#include <AdamLib/Nodes/Node.hpp>

#include "test.hpp"


uint64_t frame_time = 0;


//temporary, blow this bitch up eventually
void limitFPS()
{
  static const uint64_t goal_frame_time = (1000/60);

  frame_time = SDL_GetTicks() - frame_time;

  if(frame_time < goal_frame_time)
  {
    SDL_Delay(goal_frame_time - frame_time);
  }
}

using namespace AdamLib;

void print(double, Node*)
{
  static int i = 0;
  std::cout << "Print: " << ++i << std::endl;
}

int main(int argc, char** argv)
{

  SDL_Init(SDL_INIT_VIDEO);
  GameWindow& ref = GameWindow::getInstance();

  Node& roo = Node::getRoot();

  loadgame();


  int i=0;
  while(Input::processEvents())
  {
    limitFPS();
    frame_time = SDL_GetTicks();

    roo.process(0.0166666);
    Renderer::render_all();
    Node::freeQueued();
  }

  roo.immediatelyKillAllChildren();  

  return 0;
}