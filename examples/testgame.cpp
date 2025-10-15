#include "test.hpp"
#include <AdamLib/Nodes/Node.hpp>
#include <AdamLib/Nodes/SpriteNode.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>

#include <AdamLib/Math.hpp>
#include <AdamLib/Input.hpp>

#include <AdamLib/Collision/CollisionDetector.hpp>


using namespace AdamLib;
#define SPEED 500;

CollisionDetector detector({1280, 720});


struct Player : SpriteNodeInstanceController
{
  Vec2 velocity{0,0};


  void process(double _dT) override
  {
    self()->movePos(velocity * _dT);
    detector.updateTree();
    detector.queryTreeForCollisions();
  }

  void ready() override
  {
    RegisterKeyChangeConnection(KEY_UP,  onMovementInputChange);
    RegisterKeyChangeConnection(KEY_LEFT, onMovementInputChange);
    RegisterKeyChangeConnection(KEY_DOWN, onMovementInputChange);
    RegisterKeyChangeConnection(KEY_RIGHT, onMovementInputChange);
    RegisterKeyChangeConnection(KEY_0, printTree);


  }

  void printTree()
  {

  }

  void onMovementInputChange()
  {
    velocity.y = (Input::keystate(KEY_DOWN) - Input::keystate(KEY_UP));
    velocity.x = (Input::keystate(KEY_RIGHT) - Input::keystate(KEY_LEFT));

    velocity = Vec2::normalize(velocity) * SPEED;
  }

  


};



void loadgame()
{
  Node& roo = Node::getRoot();


  SpriteTemplate player_node("Player_Sprite", "assets/square144.png", new Player());
  player_node.default_pos_ = {000,000};
  player_node.layer_ = 2;

  SpriteTemplate box_node("Box_Node", "assets/square144.png");
  box_node.default_pos_ = {500,500};
  box_node.layer_ = 2;



  CollisionTemplate player_collision("Player_Collision", new CollisionRectangle({0,0}, {144,144}));

  CollisionTemplate box_collision("Box_Collision", new CollisionRectangle({0,0}, {144,144}));


  player_node.registerChildTemplate(&player_collision);
  box_node.registerChildTemplate(&box_collision);




  roo.addChild(player_node.createInstance());
  roo.addChild(box_node.createInstance());


  detector.addCollisionNode((CollisionNode*)roo.getMyChild("Player_Sprite/Player_Collision"));
  detector.addCollisionNode((CollisionNode*)roo.getMyChild("Box_Node/Box_Collision"));

}