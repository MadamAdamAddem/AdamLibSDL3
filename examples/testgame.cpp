#include "AdamLib/Nodes/Node.hpp"
#include <AdamLib/Collision/CollisionShapes.hpp>
#include <AdamLib/Utilities/Math.hpp>
#include <AdamLib/Nodes/SpriteNode.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>
#include <AdamLib/Core/Input.hpp>

using namespace AdamLib;

struct TestController : NodeInstanceController
{
  void process(double _dT) override
  {
    if(Input::keystate(KEY_P))
      self()->setPos(Vec2(400,400));
  }
};

NodeTemplate testnode("Test_Node", NodeController(TestController));
SpriteNodeTemplate childnode("Child_Node", "square144.png");

void loadgame()
{
  Node& root = Node::getRoot();
  testnode.default_pos_ = {200,200};
  testnode.registerChildTemplate(&childnode);

  root.addChild(testnode.createInstance());

}