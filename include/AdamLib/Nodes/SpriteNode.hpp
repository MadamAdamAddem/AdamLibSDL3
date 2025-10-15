#pragma once
#include <AdamLib/Nodes/Node.hpp>
#include <AdamLib/Resources/Texture.hpp>

namespace AdamLib
{

class SpriteTemplate;
class SpriteNodeInstanceController;

class SpriteNode : public Node
{
  friend class SpriteTemplate;
  TextureInstance texture_;
public:

  SpriteNode(const std::string& _name, const std::string& _img_path, NodeInstanceController* _controller, Node* _parent = nullptr);
  virtual ~SpriteNode();

  void changeTexture(const std::string& _img_path, ScaleMode _scale_mode = NEAREST);
  void setLayer(unsigned layer);
  void setTextureStretch(const Vec2& _scale);
  void setVisibility(bool visible);
  void toggleVisibility();

  virtual void setPos(const Vec2& _pos) override;
  virtual void movePos(const Vec2& _move) override;


  void setClip();
};


class SpriteTemplate : public NodeTemplate
{
public:
  SpriteTemplate(const std::string& _name, const std::string& _img_path, NodeInstanceController* _controller = nullptr);
  std::string path_to_sprite_;

  virtual Node* createInstance() override;

  Vec2 default_stretch_{1,1};
  unsigned layer_{1};

};

struct SpriteNodeInstanceController : public NodeInstanceController
{
  SpriteNodeInstanceController() = default;
  SpriteNode* self() override;
};


}