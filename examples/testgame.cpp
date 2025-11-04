#include <AdamLib/Collision/CollisionShapes.hpp>
#include <AdamLib/Utilities/Math.hpp>
#include <AdamLib/Nodes/SpriteNode.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>
#include <AdamLib/Core/Input.hpp>

using namespace AdamLib;


struct Player : SpriteNodeInstanceController
{
  double speed = 20;
  Vec2 velocity{0,0};

  void process(double _dt) override
  {
    self()->movePos(velocity);
  }

  void onReady() override
  {
    RegisterKeyChangeConnection(KEY_RIGHT, doMovement);
    RegisterKeyChangeConnection(KEY_LEFT, doMovement);
    RegisterKeyChangeConnection(KEY_UP, doMovement);
    RegisterKeyChangeConnection(KEY_DOWN, doMovement);
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

}