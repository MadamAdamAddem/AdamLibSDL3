#include <AdamLib/Collision/CollisionDetector.hpp>

using namespace AdamLib;

CollisionDetector::CollisionDetector(Vec2 _dimensions) : tree_(0.05, _dimensions)
{
  
}

void CollisionDetector::addCollisionNode(CollisionNode* _addition)
{
  if(contained_nodes_.insert(_addition).second == true)
  {
    auto newbottomleft = _addition->shape_->aabb_.bottom_left_ + _addition->getPos();
    auto newtopright = _addition->shape_->aabb_.top_right_ + _addition->getPos();
    tree_.insertParticle(_addition, newbottomleft, newtopright);

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
    std::vector<void*> colliders = tree_.query(node);
    for(void* collider : colliders)
    {
      node->determineCollisionWith((CollisionNode*)collider);
    }
  }
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
  tree_.updateParticle(_update, _update->shape_->aabb_.bottom_left_ + _update->getPos(), _update->shape_->aabb_.top_right_ + _update->getPos());
}
