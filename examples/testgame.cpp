#include <iostream>
#include <ostream>
#include <AdamLib/Collision/CollisionShapes.hpp>
#include <AdamLib/Utilities/Math.hpp>
#include <AdamLib/Nodes/SpriteNode.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>
#include <AdamLib/Collision/CollisionDetector.hpp>
#include <AdamLib/Core/Input.hpp>

using namespace AdamLib;

CollisionDetector detector({1280, 720});

struct Player : SpriteNodeInstanceController
{
  double speed = 500;
  Vec2 velocity{0,0};
  Signal<double, int> dick;

  void dodick(double d, int p)
  {
    static bool vis = false;
    self()->setVisibility(vis);
    vis = !vis;
  }

  void process(double _dt) override
  {
    self()->movePos(velocity * _dt);
  }

  void onReady() override
  {
    RegisterKeyChangeConnection(KEY_RIGHT, doMovement);
    RegisterKeyChangeConnection(KEY_LEFT, doMovement);
    RegisterKeyChangeConnection(KEY_UP, doMovement);
    RegisterKeyChangeConnection(KEY_DOWN, doMovement);
    RegisterKeyChangeConnection(KEY_Q, dosig);
    RegisterCustomConnection(dick, dodick);

  }

  void dosig()
  {
    dick.emit(2, 3);
  }

  void doMovement()
  {
    velocity.x = Input::keystate(KEY_RIGHT) - Input::keystate(KEY_LEFT);
    velocity.y = Input::keystate(KEY_DOWN) - Input::keystate(KEY_UP);

    velocity.normalize();
    velocity *= speed;
  }

};

SpriteNodeTemplate player_spr{"Player_Sprite", "assets/goated.jpg", SpriteController(Player)};
CollisionNodeTemplate player_coll{"Player_Collision", CollisionRectangle(Vec2(0,0), 144, 144)};



void loadgame()
{

  Node& root = Node::getRoot();
  player_spr.default_pos_ = {200,200};
  player_spr.registerChildTemplate(&player_coll);

  player_coll.renderCollision = true;



  root.addChild(player_spr.createInstance());
  CollisionNode* n = (CollisionNode*)root.getMyChild("Player_Sprite/Player_Collision");
  detector.addCollisionNode(n);
}