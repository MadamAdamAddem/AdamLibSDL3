#pragma once
#include <AdamLib/Nodes/Node.hpp>
#include <AdamLib/Resources/Texture.hpp>

namespace AdamLib
{

class SpriteNodeTemplate;
class SpriteNodeInstanceController;

//! Node derivative that contains a texture instance
/*!
    Holds a texture instance provided by img path, with some management functions.
*/
class SpriteNode : public Node
{
protected:
  friend class SpriteNodeTemplate;
  TextureInstance texture_;
public:

  SpriteNode(const std::string& _name, const std::string& _img_path, NodeInstanceController* _controller = nullptr, Node* _parent = nullptr);
  virtual ~SpriteNode();

  void changeTexture(const std::string& _img_path, ScaleMode _scale_mode = NEAREST);
  void setLayer(unsigned layer);
  void setTextureStretch(const Vec2& _scale);
  void setVisibility(bool visible);
  void toggleVisibility();

  virtual void setPos(const Vec2& _pos) override;
  virtual void movePos(const Vec2& _move) override;

};


class SpriteNodeTemplate : public NodeTemplate
{
protected:
  Node* createNode(NodeInstanceController* _controller) override; 


public:
  SpriteNodeTemplate(const std::string& _name, const std::string& _img_path, std::function<NodeInstanceController*()> _controller_factory = nullptr);
  std::string path_to_sprite_;

  Vec2 default_stretch_{1,1};
  bool hidden_{false};
  unsigned layer_{1};

};

struct SpriteNodeInstanceController : public NodeInstanceController
{
  SpriteNodeInstanceController() = default;
  SpriteNode* self() override;
};


}