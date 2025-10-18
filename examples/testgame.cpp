#include "AdamLib/Collision/CollisionShapes.hpp"
#include "test.hpp"
#include <AdamLib/Nodes/Node.hpp>
#include <AdamLib/Nodes/SpriteNode.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>

#include <AdamLib/Math.hpp>
#include <AdamLib/Input.hpp>

#include <AdamLib/Collision/CollisionDetector.hpp>

#include <iostream>


using namespace AdamLib;

CollisionDetector detector({1280, 720});



struct Player : CollisionNodeInstanceController
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

  void onCollisionWith(CollisionNode* _n) override
  { 
    std::cout << "Collision Yippie!" << std::endl;
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



void loadgame()
{
  Node& roo = Node::getRoot();


  SpriteNodeTemplate player_sprite("Player_Sprite", "assets/square144.png", Controller(Player));
  CollisionNodeTemplate player_collision("Player_Collision", Rectangle(Vec2(0,0), 144, 144));

  player_sprite.registerChildTemplate(&player_collision);

  CollisionNodeTemplate box_collision("Box_Collision", Rectangle(Vec2(500,500), 144, 144));

  CollisionNodeTemplate ray_collision("Ray_Collision", Ray(Vec2(500, 200), Vec2(1,1), 50));


  Node* playernode = player_sprite.createInstance();
  Node* boxnode = box_collision.createInstance();
  Node* raynode = ray_collision.createInstance();

  roo.addChild(playernode);
  roo.addChild(boxnode);
  roo.addChild(raynode);


  detector.addCollisionNode((CollisionNode*)boxnode);
  detector.addCollisionNode((CollisionNode*)raynode);

}