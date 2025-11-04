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
  friend class SpriteNodeTemplate;


protected:
  TextureInstance texture_;

  SpriteNode(const std::string& _name, const std::string& _img_path, NodeInstanceController* _controller = nullptr, Node* _parent = nullptr);
public:


  void changeTexture(const std::string& _img_path, ScaleMode _scale_mode = NEAREST);
  void setLayer(unsigned layer);
  void setTextureStretch(const Vec2& _scale);
  void setVisibility(bool visible);
  void toggleVisibility();

  virtual void movePos(const Vec2& _move) override;

};


class SpriteNodeTemplate : public NodeTemplate
{
protected:
  Node* createNode(NodeInstanceController* _controller) override; 
public:
  SpriteNodeTemplate(const std::string& _name, const std::string& _img_path, std::function<SpriteNodeInstanceController*()> _controller_factory = nullptr);
  std::string path_to_sprite_;

  Vec2 default_stretch_{1,1};
  bool hidden_{false};
  unsigned layer_{1};

};

struct SpriteNodeInstanceController : public NodeInstanceController
{
  SpriteNodeInstanceController() = default;
  SpriteNode* self() override;
  virtual ~SpriteNodeInstanceController() = default;
};


#define SpriteController(Typename) [] () -> SpriteNodeInstanceController* {return static_cast<SpriteNodeInstanceController*>(new Typename());}

}