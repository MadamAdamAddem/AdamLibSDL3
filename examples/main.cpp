#include <AdamLib/Core/AdamLib.hpp>
#include <AdamLib/Core/Rendering.hpp>
#include <AdamLib/Input.hpp>
#include <AdamLib/Nodes/Node.hpp>

#include "test.hpp"


using namespace AdamLib;

int main(int argc, char** argv)
{
  initialize();
  Node& root = Node::getRoot();

  loadgame();


  int i=0;
  while(Input::processEvents())
  {
    limitFPS(60);

    root.process(0.0166666);
    Node::freeQueued();
    Renderer::render_all();
  }

  root.immediatelyKillAllChildren();  

  return 0;
}