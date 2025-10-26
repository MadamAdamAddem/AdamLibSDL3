#include "AdamLib/Collision/CollisionShapes.hpp"
#include <AdamLib/Nodes/Node.hpp>
#include <AdamLib/Nodes/SpriteNode.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>

#include <AdamLib/Math.hpp>
#include <AdamLib/Input.hpp>

#include <AdamLib/Collision/CollisionDetector.hpp>



using namespace AdamLib;


struct Player : SpriteNodeInstanceController
{
  Vec2 velocity{0,0};

  float speed_{500};

  void process(double _dT) override
  {
    self()->movePos(velocity * _dT);
  }

  void onReady() override
  {
    RegisterKeyChangeConnection(KEY_UP,  onMovementInputChange);
    RegisterKeyChangeConnection(KEY_LEFT, onMovementInputChange);
    RegisterKeyChangeConnection(KEY_DOWN, onMovementInputChange);
    RegisterKeyChangeConnection(KEY_RIGHT, onMovementInputChange);
    RegisterKeyChangeConnection(KEY_LSHIFT, onMovementInputChange);
  }

  void onMovementInputChange()
  {
    if(Input::keystate(KEY_LSHIFT))
      speed_ = 50;
    else
      speed_ = 500;

    velocity.y = (Input::keystate(KEY_DOWN) - Input::keystate(KEY_UP));
    velocity.x = (Input::keystate(KEY_RIGHT) - Input::keystate(KEY_LEFT));

    velocity = Vec2::normalize(velocity) * speed_;
  }
  

};

SpriteNodeTemplate player_spr{"Player_Sprite", "assets/square144.png", SpriteController(Player)};
CollisionNodeTemplate player_coll{"Player_Collision", Rectangle(Vec2(0,0), 144, 144)};


struct GlobalController : NodeInstanceController
{
  void onReady() override
  {
    RegisterKeyChangeConnection(KEY_0, createNewPlayer);
    RegisterKeyChangeConnection(KEY_P, printTree);
  }

  void createNewPlayer()
  {
    if(Input::keystate(KEY_0))
      Node::getRoot().addChild(player_spr.createInstance());
  }

  void printTree()
  {
    if(Input::keystate(KEY_P))
      Node::printTree();
  }

};

void loadgame()
{

  Node& roo = Node::getRoot();

  NodeTemplate global{"Global", NodeController(GlobalController)};

  player_spr.default_pos_ = {300,300};
  player_spr.registerChildTemplate(&player_coll);
  player_coll.renderCollision = true;

  roo.addChild(player_spr.createInstance());
  roo.addChild(global.createInstance());


}