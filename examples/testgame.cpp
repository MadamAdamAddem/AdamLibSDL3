#include <AdamLib/Nodes/SpriteNode.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>
#include <AdamLib/Input.hpp>

using namespace AdamLib;

Signal<> leftclick;


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


SpriteNodeTemplate player{"Player_Sprite", "assets/goated.jpg", SpriteController(Player)};
CollisionNodeTemplate player_coll{"Player_Collision", CollisionRectangle(Vec2(0,0), 144, 144)};

SpriteNodeTemplate enemy{"Enemy_Sprite", "assets/square144.png"};


struct Global : NodeInstanceController
{
  void onReady() override
  {
    RegisterKeyChangeConnection(KEY_E, spawnEnemy);
  }

  void spawnEnemy()
  {
    if(Input::keystate(KEY_E))
    {
      Node& root = Node::getRoot();
      SpriteNode* new_enemy = static_cast<SpriteNode*>(enemy.createInstance());
      new_enemy->setPos({400, 400});
      root.addChild(new_enemy);
    }
  }


};
NodeTemplate global{"Global", NodeController(Global)};



void loadgame()
{

  Node& root = Node::getRoot();

  player.registerChildTemplate(&player_coll);
  player.default_pos_ = {200,200};
  player_coll.renderCollision = true;

  enemy.default_pos_ = {500,500};


  root.addChild(player.createInstance());

}