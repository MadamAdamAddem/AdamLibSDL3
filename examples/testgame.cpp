#include "AdamLib/Collision/CollisionShapes.hpp"
#include <AdamLib/Nodes/Node.hpp>
#include <AdamLib/Nodes/SpriteNode.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>

#include <AdamLib/Math.hpp>
#include <AdamLib/Input.hpp>

#include <AdamLib/Collision/CollisionDetector.hpp>

#include <iostream>


using namespace AdamLib;

CollisionDetector detector({1280, 720});


struct Player : SpriteNodeInstanceController
{
  Vec2 velocity{0,0};

  float speed_{500};

  void process(double _dT) override
  {
    self()->movePos(velocity * _dT);
    detector.updateTree();
    detector.queryTreeForCollisions();
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

    velocity.normalize();
    velocity *= speed_;
  }
  
};

struct PlayerColl : CollisionNodeInstanceController
{
  void onCollisionWith(CollisionNode *_collider)
  {
    static int i = 0;
    std::cout << "Collided with: " << _collider->getName() << " " << ++i << std::endl;
  }
};

SpriteNodeTemplate player_spr{"Player_Sprite", "assets/square144.png", SpriteController(Player)};
CollisionNodeTemplate player_coll{"Player_Collision", CollisionCircle(Vec2(0,0), 100), CollisionController(PlayerColl)};

SpriteNodeTemplate box_spr{"Box_Sprite", "assets/square144.png"};
CollisionNodeTemplate box_coll{"Box_Collision", CollisionRectangle(Vec2(0,0), 144, 144)};

struct GlobalController : NodeInstanceController
{
  void onReady() override
  {
    RegisterKeyChangeConnection(KEY_P, printTree);
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

  
  box_spr.default_pos_ = {500,500};
  box_spr.registerChildTemplate(&box_coll);
  box_coll.renderCollision = true;
  
  Node* player = player_spr.createInstance();
  CollisionNode* pcoll = (CollisionNode*)player->getMyChild("Player_Collision");
  Node* box = box_spr.createInstance();
  CollisionNode* boxcoll = (CollisionNode*)box->getMyChild("Box_Collision");

  roo.addChild(player);
  roo.addChild(box);
  detector.addCollisionNode(pcoll);
  detector.addCollisionNode(boxcoll);

}