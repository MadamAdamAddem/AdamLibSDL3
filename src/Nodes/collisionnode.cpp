#include "AdamLib/Collision/CollisionShapes.hpp"
#include "AdamLib/Math.hpp"
#include <AdamLib/Defines.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>

#define CUTE_C2_IMPLEMENTATION
#include <AdamLib/Collision/cute_c2.hpp>

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include <iostream>
#include <assert.h>


using namespace AdamLib;

c2AABB aabbConversion(AABB _aabb)
{
  Vec2& bl = _aabb.bottom_left_;
  Vec2& tr = _aabb.top_right_;

  return {{(float)bl.x, (float)-bl.y}, {(float)tr.x, (float)-tr.y}};
}

c2Circle circleConversion(CollisionCircle* _circle)
{
  return {{(float)_circle->offset_.x, (float)-_circle->offset_.y}, _circle->r_};
}


CollisionNode::CollisionNode(const std::string& _name, CollisionShape* _shape, NodeInstanceController* _controller,  Node* _parent) : 
  Node(_name, _controller, _parent), shape_(_shape)
{
  assert(_shape != nullptr);

}

CollisionNode::~CollisionNode()
{

}

//this is a mess
void CollisionNode::determineCollisionWith(CollisionNode* _collider)
{
  using ShapeType = CollisionShape::ShapeType;
  ShapeType type = _collider->shape_->shapetype_;
  Vec2& collpos = _collider->pos_;
  AABB& collaabb = _collider->shape_->aabb_;

  bool isCollision = false;

  switch(type)
  {
    case ShapeType::RECTANGLE:
      isCollision = determineCollisionWithRect({collaabb.bottom_left_ + collpos, collaabb.top_right_ + collpos});
      break;      

    case ShapeType::CIRCLE:
    {
      CollisionCircle* collcircle = (CollisionCircle*)_collider->shape_.get();
      isCollision = determineCollisionWithCircle(collcircle->offset_ + collpos, collcircle->r_);
    }
      break;

    case ShapeType::CAPSULE:
    {
      CollisionCapsule* collcap = (CollisionCapsule*)_collider->shape_.get();
      isCollision = determineCollisionWithCapsule(collcap->a_offset_ + collpos, collcap->b_offset_ + collpos, collcap->r_);
    }
      break;

    case ShapeType::RAY:
      return;

    case ShapeType::POLYGON:
    case ShapeType::INVALID:
    default:
      std::cerr << "Shape Type not supported" << std::endl;
      exit(1);
  }

  if(isCollision && controller_)
  {
    ((CollisionNodeInstanceController*)controller_.get())->onCollisionWith(_collider);
  }
}

bool CollisionNode::determineCollisionWithRect(AABB _rect)
{
  using ShapeType = CollisionShape::ShapeType;
  ShapeType type = shape_->shapetype_;

  c2AABB colliderrect = aabbConversion(_rect);

  switch(type)
  {
    case ShapeType::RECTANGLE:
    {
      c2AABB myrect = aabbConversion({shape_->aabb_.bottom_left_ + pos_, shape_->aabb_.top_right_ + pos_});
      return c2AABBtoAABB(myrect, colliderrect);
    }

    case ShapeType::CIRCLE:
    {
      c2Circle mycirc = circleConversion((CollisionCircle*)shape_.get());
      mycirc.p.x += pos_.x;
      mycirc.p.y -= pos_.y;
      return c2CircletoAABB(mycirc, colliderrect);
    }

    case ShapeType::RAY:
      return false;

    case ShapeType::CAPSULE:
    case ShapeType::POLYGON:
    case ShapeType::INVALID:
    default:
      std::cerr << "Shape Type not supported" << std::endl;
      exit(1);
  }
}

bool CollisionNode::determineCollisionWithCircle(Vec2 _center, float _r)
{
  return false;
}

bool CollisionNode::determineCollisionWithCapsule(Vec2 _apos, Vec2 _bpos, float _r)
{
  return false;
}



#ifdef DRAW_COLLISION
#include <AdamLib/Core/Rendering.hpp>

void CollisionNode::movePos(const Vec2& _move)
{
  Node::movePos(_move);
  shape_->updatePos(pos_);
}
#endif



/*----- CollisionTemplate -----*/

CollisionNodeTemplate::CollisionNodeTemplate(const std::string& _name, std::function<CollisionShape*()> _shape_factory, std::function<NodeInstanceController*()> _controller_factory) : 
  NodeTemplate(_name, _controller_factory), 
  shape_factory_(_shape_factory)
{

}

Node* CollisionNodeTemplate::createNode(NodeInstanceController* _controller)
{
  return new CollisionNode(default_name_, shape_factory_(), _controller);
}
/*----- CollisionTemplate -----*/

/*----- CollisionNodeInstanceController -----*/


CollisionNode* CollisionNodeInstanceController::self() {return (CollisionNode*)(self_);}

void CollisionNodeInstanceController::onCollisionWith(CollisionNode* _collider) {}


/*----- CollisionNodeInstanceController -----*/
