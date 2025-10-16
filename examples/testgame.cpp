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

  void ready() override
  {
    RegisterKeyChangeConnection(KEY_UP,  onMovementInputChange);
    RegisterKeyChangeConnection(KEY_LEFT, onMovementInputChange);
    RegisterKeyChangeConnection(KEY_DOWN, onMovementInputChange);
    RegisterKeyChangeConnection(KEY_RIGHT, onMovementInputChange);
    RegisterKeyChangeConnection(KEY_LSHIFT, onMovementInputChange);
    RegisterKeyChangeConnection(KEY_0, printTree);


  }

  void printTree()
  {

  }

  void onCollisionWith(CollisionNode* _collider) override
  {
    std::cout << "Player Collision With: " << _collider->name_ << std::endl;
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




  CollisionTemplate player_collision("Player_Collision", new CollisionRectangle({0,0}, {144,144}), new Player());

  CollisionTemplate box_collision("Box_Collision", new CollisionRectangle({500,500}, {144,144}));

  CollisionTemplate ray_collision("Ray_Collision", new CollisionRay({500, 200}, {1,1}, 50));


  Node* playernode = player_collision.createInstance();
  Node* boxnode = box_collision.createInstance();
  Node* raynode = ray_collision.createInstance();

  roo.addChild(playernode);
  roo.addChild(boxnode);
  roo.addChild(raynode);


  detector.addCollisionNode((CollisionNode*)playernode);
  detector.addCollisionNode((CollisionNode*)boxnode);
  detector.addCollisionNode((CollisionNode*)raynode);

}