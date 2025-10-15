#pragma once

#include <AdamLib/Defines.hpp>
#include <AdamLib/Math.hpp>

#include <AdamLib/Nodes/Node.hpp>
#include <AdamLib/Collision/CollisionShapes.hpp>

#include <memory>



#define MAX_POLYGON_VERTEXS 8

namespace AdamLib
{

class CollisionNode;
class CollisionTemplate;
class CollisionNodeInstanceController;


class CollisionNode : public Node
{
  friend class CollisionNodeTemplate;

public:
  CollisionNode(const std::string& _name, CollisionShape* _shape, NodeInstanceController* _controller = nullptr, Node* _parent = nullptr);
  ~CollisionNode();

  void determineCollisionWith(CollisionNode* _collider);

  #ifdef DRAW_COLLISION
  virtual void movePos(const Vec2& _move) override;
  #endif

  std::unique_ptr<CollisionShape> shape_;

};


class CollisionTemplate : public NodeTemplate
{
public:
  CollisionTemplate(const std::string& _name, CollisionShape* _shape, NodeInstanceController* _controller = nullptr);
  virtual Node* createInstance() override;

  CollisionShape* shape_;

};

struct CollisionNodeInstanceController : public NodeInstanceController
{
  CollisionNodeInstanceController() = default;
  CollisionNode* self() override;
};




}