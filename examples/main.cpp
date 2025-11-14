#include <AdamLib/Core/AdamLib.hpp>
#include <AdamLib/Core/Rendering.hpp>
#include <AdamLib/Core/Input.hpp>
#include <AdamLib/Nodes/Node.hpp>
#include "test.hpp"

using namespace AdamLib;

int main(int argc, char** argv)
{
  initialize();
  loadgame();             
  Node& root = Node::getRoot();

  while(Input::processEvents()) 
  {
    limitFPS(60); 

    root.process(1.0/60); 
    Node::freeQueued();      
    Renderer::render_all();  
  }

  root.immediatelyKillAllChildren();
  return 0;
}