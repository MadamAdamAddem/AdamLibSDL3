#include <AdamLib/Collision/CollisionDetector.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>
#include <AdamLib/Defines.hpp>

using namespace AdamLib;

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
      node->determineCollisionWith(collider);
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
  tree_.updateParticle(_update);
}
