#include <AdamLib/Defines.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#define CUTE_C2_IMPLEMENTATION
#include <AdamLib/Collision/cute_c2.hpp>


using namespace AdamLib;


CollisionNode::CollisionNode(const std::string& _name, CollisionShape* _shape, NodeInstanceController* _controller,  Node* _parent) : 
  Node(_name, _controller, _parent), shape_(_shape)
{

}

CollisionNode::~CollisionNode()
{

}


void CollisionNode::determineCollisionWith(CollisionNode* _collider)
{

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

CollisionTemplate::CollisionTemplate(const std::string& _name, CollisionShape* _shape, NodeInstanceController* _controller) : 
  NodeTemplate(_name, _controller), 
  shape_(_shape)
{

}

Node* CollisionTemplate::createInstance()
{  
  CollisionNode* self = new CollisionNode(name_, shape_, controller_);

  for(auto& c : children_)
  {
    self->addChild(c->createInstance());
  }

  self->setPos(default_pos_);

  return self;
}

/*----- CollisionTemplate -----*/

/*----- CollisionNodeInstanceController -----*/


CollisionNode* CollisionNodeInstanceController::self() {return (CollisionNode*)(subject_);}


/*----- CollisionNodeInstanceController -----*/
