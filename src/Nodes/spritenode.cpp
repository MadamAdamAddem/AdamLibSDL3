#include <AdamLib/Nodes/SpriteNode.hpp>

using namespace AdamLib;




/*----- SpriteNode -----*/

SpriteNode::SpriteNode(const std::string& _name, const std::string& _img_path, NodeInstanceController* _controller, Node* _parent) : 
  Node(_name, _controller, _parent), 
  texture_(_img_path)
{

}

void SpriteNode::changeTexture(const std::string& _img_path, ScaleMode _scale_mode)
{
  texture_.changeTexture(_img_path, _scale_mode);
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

/*----- SpriteNode -----*/


/*----- SpriteNodeTemplate -----*/

SpriteNodeTemplate::SpriteNodeTemplate(const std::string& _name, const std::string& _img_path, std::function<SpriteNodeInstanceController*()> _controller_factory) : 
  NodeTemplate(_name, _controller_factory), 
  path_to_sprite_(_img_path)
{
}


Node* SpriteNodeTemplate::createNode(NodeInstanceController* _controller)
{
  SpriteNode* instance = new SpriteNode(default_name_, path_to_sprite_, _controller);
  instance->setLayer(layer_);
  instance->setVisibility(!hidden_);
  instance->setTextureStretch(default_stretch_);
  if(!hidden_)
    instance->texture_.addToRenderer();
  
  return instance;
}

/*----- SpriteNodeTemplate -----*/





SpriteNode* SpriteNodeInstanceController::self() {return static_cast<SpriteNode*>(self_);}