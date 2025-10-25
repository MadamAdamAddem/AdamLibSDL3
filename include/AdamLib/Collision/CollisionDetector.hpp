#pragma once
#include <AdamLib/Math.hpp>
#include <AdamLib/Collision/AABB.hpp>
#include <unordered_set>

namespace AdamLib
{

class CollisionNode;

//! A Broad-Phase Collision Detection Tree
/*! 
    Contains a dynamic AABB Tree. 
    When a possible collision is detected, both nodes involved are sent each-other to determine collision status.

    All Collision Nodes entering the tree must at some time remove themselves from the tree. This must occur to prevent segfaults.
*/
class CollisionDetector
{
  std::unordered_set<CollisionNode*> contained_nodes_;
  aabb::Tree tree_;

public:
  CollisionDetector(Vec2 _dimensions);
  
  //! Add collision node to detection tree
  /*! \param _addition
        The node to be added
  */
  void addCollisionNode(CollisionNode* _addition);

  //! Remove collision node from detection tree
  /*! \param _removal
        The node to be removed
  */
  void removeCollisionNode(CollisionNode* _removal);
  
  //! Iterates over each node and checks for possible collisions
  //! Calls on each node to determine narrow-phase collision if possible collision found
  void queryTreeForCollisions();

  //! Updates the position of each node
  void updateTree();

  //! Updates the position of specified node
  /*! \param _update
        The node to be updated, using Node::getPos()
  */
  void updateNodePosition(CollisionNode* _update);

};

}