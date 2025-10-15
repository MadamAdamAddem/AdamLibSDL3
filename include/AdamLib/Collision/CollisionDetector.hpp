#pragma once
#include <AdamLib/Math.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>
#include <AdamLib/Collision/AABB.hpp>
#include <unordered_set>

namespace AdamLib
{


/*

  To Do:
    -Implement some sort of global detection system
    -Only update tree when collision object has moved

*/
class CollisionDetector
{
  std::unordered_set<CollisionNode*> contained_nodes_;
  aabb::Tree tree_;

public:
  CollisionDetector(Vec2 _dimensions);
  
  void addCollisionNode(CollisionNode* _addition);
  void removeCollisionNode(CollisionNode* _emmigrant);
  
  void queryTreeForCollisions();
  void updateTree();
  void updateNodePosition(CollisionNode* _update);

};

}