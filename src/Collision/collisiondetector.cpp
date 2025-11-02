#include "AdamLib/Collision/CollisionShapes.hpp"
#include <AdamLib/Collision/CollisionDetector.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>
#include <AdamLib/Defines.hpp>

#include "cute_c2.hpp"
#include <assert.h>

using namespace AdamLib;



inline c2AABB aabbConversion(const CollisionRectangle* _rect)
{
  return {{_rect->center_.x - _rect->width_height_.x/2, _rect->center_.y + _rect->width_height_.y/2}, {_rect->center_.x + _rect->width_height_.x/2, _rect->center_.y - _rect->width_height_.y/2}};
}

inline c2Circle circleConversion(const CollisionCircle* _circle)
{
  return {{_circle->center_.x, -_circle->center_.y}, _circle->r_};
}

inline c2Capsule capsuleConversion(const CollisionCapsule* _capsule)
{
  return {{_capsule->a_center_.x, _capsule->a_center_.y }, {_capsule->b_center_.x, _capsule->b_center_.y}, _capsule->r_};
}

CollisionDetector::CollisionDetector(const Vec2& _dimensions) : tree_(SKIN_THICKNESS, _dimensions)
{
  
}

void CollisionDetector::addCollisionNode(CollisionNode* _addition)
{
  if(contained_nodes_.insert(_addition).second == true)
  {
    tree_.insertParticle(_addition);
  }

}

void CollisionDetector::removeCollisionNode(CollisionNode* _removal)
{
  if(contained_nodes_.erase(_removal) == 1)
  {
    tree_.removeParticle(_removal);
  }
}


void CollisionDetector::queryTreeForCollisions()
{
  for(auto node : contained_nodes_)
  {
    std::vector<CollisionNode*> colliders = tree_.query(node);
    for(CollisionNode* collider : colliders)
    {
      if(determineCollisionBetween(node, collider))
      {
        if(node->controller_)
        {
          static_cast<CollisionNodeInstanceController*>(node->controller_.get())->onCollisionWith(collider);
        }

        if(collider->controller_)
        {
          static_cast<CollisionNodeInstanceController*>(collider->controller_.get())->onCollisionWith(node);
        }
      }
    }
  }
}

bool CollisionDetector::determineCollisionBetween(CollisionNode* _c1, CollisionNode* _c2)
{
  C2_TYPE type1, type2;
  c2AABB rect1, rect2;
  c2Circle circ1, circ2;
  c2Capsule cap1, cap2;
  void *c2_1 = NULL, *c2_2 = NULL;


  if(CollisionRectangle* rect = std::get_if<CollisionRectangle>(&_c1->shape_))
  {
    type1 = C2_TYPE_AABB;
    rect1 = aabbConversion(rect);
    c2_1 = &rect1;
  }
  else if(CollisionCircle* circ = std::get_if<CollisionCircle>(&_c1->shape_))
  {
    type1 = C2_TYPE_CIRCLE;
    circ1 = circleConversion(circ);
    c2_1 = &circ1;
  }
  else if(CollisionCapsule* caps = std::get_if<CollisionCapsule>(&_c1->shape_))
  {
    type1 = C2_TYPE_CAPSULE;
    cap1 = capsuleConversion(caps);
    c2_1 = &cap1;
  }
  else if(CollisionRay* ray = std::get_if<CollisionRay>(&_c1->shape_))
  {
    assert(0);
  }
  else
    assert(0);


  if(CollisionRectangle* rect = std::get_if<CollisionRectangle>(&_c2->shape_))
  {
    type2 = C2_TYPE_AABB;
    rect2 = aabbConversion(rect);
    c2_2 = &rect2;
  }
  else if(CollisionCircle* circ = std::get_if<CollisionCircle>(&_c2->shape_))
  {
    type2 = C2_TYPE_CIRCLE;
    circ2 = circleConversion(circ);
    c2_2 = &circ2;
  }
  else if(CollisionCapsule* caps = std::get_if<CollisionCapsule>(&_c2->shape_))
  {
    type2 = C2_TYPE_CAPSULE;
    cap2 = capsuleConversion(caps);
    c2_2 = &cap2;
  }
  else if(CollisionRay* ray = std::get_if<CollisionRay>(&_c2->shape_))
  {
    assert(0);
  }
  else
    assert(0);



  return c2Collided(c2_1, NULL, type1, c2_2, NULL, type2);

}


void CollisionDetector::updateTree()
{
  for(auto particle : contained_nodes_)
  {
    updateNodePosition(particle);
  }
}

void CollisionDetector::updateNodePosition(CollisionNode* _update)
{
  tree_.updateParticle(_update);
}
