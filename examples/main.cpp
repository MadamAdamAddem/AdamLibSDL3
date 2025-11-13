#include <AdamLib/Core/AdamLib.hpp>
#include <AdamLib/Core/Rendering.hpp>
#include <AdamLib/Core/Input.hpp>
#include <AdamLib/Nodes/Node.hpp>

using namespace AdamLib;

int main(int argc, char** argv)
{
  initialize();                 //Initialization
  //Custom Load Game Function Here
  Node& root = Node::getRoot();

  while(Input::processEvents())   //Input Processing
  {
    limitFPS(60);            //FPS Limiting

    root.process(1.0/60);     //Node Processing
    Node::freeQueued();           //Node Freeing
    Renderer::render_all();       //Rendering
  }

  root.immediatelyKillAllChildren();//Finalization

  return 0;
}