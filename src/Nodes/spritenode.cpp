#include <AdamLib/Nodes/SpriteNode.hpp>

using namespace AdamLib;





SpriteNode::SpriteNode(const std::string& _name, const std::string& _img_path, NodeInstanceController* _controller, Node* _parent) : 
  Node(_name, _controller, _parent), 
  texture_(_img_path)
{

}

void SpriteNode::changeTexture(const std::string& _img_path, ScaleMode _scale_mode)
{
  texture_.changeTexture(_img_path, _scale_mode);
}

void SpriteNode::setPos(const Vec2& _pos)
{
  Node::setPos(_pos);
  texture_.setRenderCenter(pos_);
}

void SpriteNode::movePos(const Vec2& _move)
{
  Node::movePos(_move);
  texture_.setRenderCenter(pos_);
}

void SpriteNode::setLayer(unsigned _layer)
{
  texture_.layer_ = _layer;
}

void SpriteNode::setVisibility(bool _visible) {texture_.hidden_ = !_visible;}

void SpriteNode::toggleVisibility() {texture_.hidden_ = !texture_.hidden_;}

void SpriteNode::setTextureStretch(const Vec2& _scale)
{
  texture_.scale_.x = _scale.x;
  texture_.scale_.y = _scale.y;
}

SpriteNode::~SpriteNode()
{
}

//

SpriteTemplate::SpriteTemplate(const std::string& _name, const std::string& _img_path, NodeInstanceController* _controller) : 
  NodeTemplate(_name, _controller), 
  path_to_sprite_(_img_path)
{

}

Node* SpriteTemplate::createInstance()
{  
  SpriteNode* self = new SpriteNode(name_, path_to_sprite_, controller_);

  for(auto& c : children_)
  {
    self->addChild(c->createInstance());
  }

  self->setPos(default_pos_);
  self->texture_.changeLayer(layer_);
  self->setTextureStretch(default_stretch_);

  return self;
}




SpriteNode* SpriteNodeInstanceController::self() {return (SpriteNode*)(subject_);}