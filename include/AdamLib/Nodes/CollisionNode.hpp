#pragma once

#include <AdamLib/Defines.hpp>
#include <AdamLib/Utilities/Math.hpp>

#include <AdamLib/Nodes/Node.hpp>
#include <AdamLib/Collision/CollisionShapes.hpp>
#include <AdamLib/Core/Rendering.hpp>
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
*/
class CollisionNode : public Node
{
  friend class CollisionNodeTemplate;
  friend class CollisionDetector;

  CollisionShape shape_;

  std::unique_ptr<Renderer::SetOfPoints> points_to_render_;
  AABB aabb_;
  bool doRendering_;

  void updatePointsToRender();

protected:
  CollisionNode(const std::string& _name, CollisionShape _shape, bool _doRendering = false, NodeInstanceController* _controller = nullptr, Node* _parent = nullptr);

public:

  virtual ~CollisionNode();

  void setCollisionRendering(bool _renderCollision);
  virtual void movePos(const Vec2& _move) override;
  inline const AABB& getAABB() {return aabb_;}

};


//! NodeTemplate derivative for CollisionNode
class CollisionNodeTemplate : public NodeTemplate
{
  CollisionShape shape_;
protected:
  virtual Node* createNode(NodeInstanceController* _controller) override; 

public:

  bool renderCollision = false;
  CollisionNodeTemplate(const std::string& _name, CollisionShape _shape, std::function<CollisionNodeInstanceController*()> _controller_factory = nullptr);

};

//! NodeInstanceController derivative for CollisionNode
struct CollisionNodeInstanceController : public NodeInstanceController
{
  CollisionNodeInstanceController() = default;
  CollisionNode* self() override;


  virtual void onCollisionWith(CollisionNode* _collider);
};

#define CollisionController(Typename) [] () -> CollisionNodeInstanceController* {return static_cast<CollisionNodeInstanceController*>(new Typename());}


}