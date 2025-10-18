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
class CollisionNodeTemplate;
class CollisionNodeInstanceController;

//! Node derivative for collision detection
/*!
    Handles narrow-phase collision detection.
    Shape contains data used in detection.
    Must be added to a Detection Tree for use, and later removed.
    Will draw collision when compiled with DRAW_COLLISION defined.
*/
class CollisionNode : public Node
{
  friend class CollisionNodeTemplate;

  bool determineCollisionWithRect(AABB _rect);
  bool determineCollisionWithCircle(Vec2 _center, float _r);
  bool determineCollisionWithCapsule(Vec2 _apos, Vec2 _bpos, float _r);

protected:
  CollisionNode(const std::string& _name, CollisionShape* _shape, NodeInstanceController* _controller = nullptr, Node* _parent = nullptr);

public:
  ~CollisionNode();

  void determineCollisionWith(CollisionNode* _collider);

  #ifdef DRAW_COLLISION
  virtual void movePos(const Vec2& _move) override;
  #endif

  std::unique_ptr<CollisionShape> shape_;

};


//! NodeTemplate derivative for CollisionNode
class CollisionNodeTemplate : public NodeTemplate
{
  std::function<CollisionShape*()> shape_factory_;
protected:
  virtual Node* createNode(NodeInstanceController* _controller) override; 
public:
  CollisionNodeTemplate(const std::string& _name, std::function<CollisionShape*()> _shape_factory, std::function<NodeInstanceController*()> _controller_factory = nullptr);
};

//! NodeInstanceController derivative for CollisionNode
struct CollisionNodeInstanceController : public NodeInstanceController
{
  CollisionNodeInstanceController() = default;
  CollisionNode* self() override;


  virtual void onCollisionWith(CollisionNode* _collider);

};



}