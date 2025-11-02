#include "AdamLib/Collision/CollisionShapes.hpp"
#include "AdamLib/Math.hpp"
#include <AdamLib/Defines.hpp>
#include <AdamLib/Nodes/CollisionNode.hpp>

#include "../Collision/cute_c2.hpp"
#include "../Core/RendererInternal.hpp"

#include <assert.h>
#include <memory>


using namespace AdamLib;

c2AABB aabbConversion(AABB _aabb)
{
  Vec2& bl = _aabb.bottom_left_;
  Vec2& tr = _aabb.top_right_;

  return {{static_cast<float>(bl.x), static_cast<float>(-bl.y)}, {static_cast<float>(tr.x), static_cast<float>(-tr.y)}};
}

c2Circle circleConversion(CollisionCircle* _circle)
{
  return {{static_cast<float>(_circle->center_.x), static_cast<float>(-_circle->center_.y)}, _circle->r_};
}


CollisionNode::CollisionNode(const std::string& _name, CollisionShape _shape, bool _doRendering, NodeInstanceController* _controller,  Node* _parent) : 
  Node(_name, _controller, _parent), shape_(_shape), doRendering_(_doRendering), points_to_render_(std::make_unique<Renderer::SetOfPoints>())
{
  if(CollisionRectangle* rect = std::get_if<CollisionRectangle>(&shape_))
  {
    Vec2 bleft = {rect->center_.x - rect->width_height_.x/2, rect->center_.y + rect->width_height_.y/2};
    Vec2 tright = {rect->center_.x + rect->width_height_.x/2, rect->center_.y - rect->width_height_.y/2};
    bleft += pos_;
    tright += pos_;

    aabb_ = {bleft, tright};
    points_to_render_->points_.resize(5);

    points_to_render_->points_[0].x = aabb_.bottom_left_.x;
    points_to_render_->points_[0].y = aabb_.bottom_left_.y;

    points_to_render_->points_[1].x = aabb_.bottom_left_.x;
    points_to_render_->points_[1].y = aabb_.top_right_.y;

    points_to_render_->points_[2].x = aabb_.top_right_.x;
    points_to_render_->points_[2].y = aabb_.top_right_.y;

    points_to_render_->points_[3].x = aabb_.top_right_.x;
    points_to_render_->points_[3].y = aabb_.bottom_left_.y;

    points_to_render_->points_[4] = points_to_render_->points_[0];
  }
  else if(CollisionCircle* circ = std::get_if<CollisionCircle>(&shape_))
  {
    aabb_ = {{circ->center_.x - circ->r_, circ->center_.y + circ->r_}, {circ->center_.x + circ->r_, circ->center_.y - circ->r_}};
    points_to_render_->points_.resize(9);
    Vec2 center = circ->center_ + pos_;
    float& radius = circ->r_; 

    points_to_render_->points_[0].x = center.x;
    points_to_render_->points_[0].y = center.y + radius;

    points_to_render_->points_[1].x = center.x - radius/2 - radius/4.3;
    points_to_render_->points_[1].y = center.y + radius/2 + radius/4.3;

    points_to_render_->points_[2].x = center.x - radius;
    points_to_render_->points_[2].y = center.y;
    
    points_to_render_->points_[3].x = center.x - radius/2 - radius/4.3;
    points_to_render_->points_[3].y = center.y - radius/2 - radius/4.3;

    points_to_render_->points_[4].x = center.x;
    points_to_render_->points_[4].y = center.y - radius;

    points_to_render_->points_[5].x = center.x + radius/2 + radius/4.3;
    points_to_render_->points_[5].y = center.y - radius/2 - radius/4.3;

    points_to_render_->points_[6].x = center.x + radius;
    points_to_render_->points_[6].y = center.y;

    points_to_render_->points_[7].x = center.x + radius/2 + radius/4.3;
    points_to_render_->points_[7].y = center.y + radius/2 + radius/4.3;

    points_to_render_->points_[8] = points_to_render_->points_[0];
    
  }
  else if(CollisionCapsule* caps = std::get_if<CollisionCapsule>(&shape_))
  {
    double rightmost = std::max(caps->a_center_.x, caps->b_center_.x) + caps->r_;
    double leftmost = std::min(caps->a_center_.x, caps->b_center_.x) - caps->r_;

    //increased y is lower height, origin is top left
    double upmost = std::min(caps->a_center_.y, caps->b_center_.y) - caps->r_;
    double downmost = std::max(caps->a_center_.y, caps->a_center_.y) + caps->r_;

    aabb_ = {{leftmost, downmost}, {rightmost, upmost}};

    points_to_render_->points_.resize(11);
  }
  else if(CollisionRay* ray = std::get_if<CollisionRay>(&shape_))
  {
    double leftmost = std::min(ray->p1_.x, ray->p2_.x);
    double rightmost = std::max(ray->p1_.x, ray->p2_.x);

    //increased y is lower height, origin is top left
    double upmost = std::min(ray->p1_.y, ray->p2_.y);
    double downmost = std::max(ray->p1_.y, ray->p2_.y);

    Vec2 bleft = {leftmost, downmost};
    Vec2 tright = {rightmost, upmost};
    bleft += pos_;
    tright += pos_;
    aabb_ = {bleft, tright};

    points_to_render_->points_.resize(2);


    points_to_render_->points_[0].x = ray->p1_.x + pos_.x;
    points_to_render_->points_[0].y = ray->p1_.y + pos_.y;

    points_to_render_->points_[1].x = ray->p2_.x + pos_.x;
    points_to_render_->points_[1].y = ray->p2_.y + pos_.y;
  }
  else
    assert(0);

  if(_doRendering)
    Renderer::addSetPoints(points_to_render_.get());
}

CollisionNode::~CollisionNode()
{
  Renderer::removeSetPoints(points_to_render_.get());
}

//this is a mess
void CollisionNode::determineCollisionWith(CollisionNode* _collider)
{

  bool isCollision = false;


  if(CollisionRectangle* rect = std::get_if<CollisionRectangle>(&_collider->shape_))
  {
    isCollision = determineCollisionWithRect({_collider->aabb_.bottom_left_, _collider->aabb_.top_right_});
  }
  else if(CollisionCircle* circ = std::get_if<CollisionCircle>(&shape_))
  {
    isCollision = determineCollisionWithCircle(circ->center_, circ->r_);
  }
  else
    assert(0);


  if(isCollision && controller_)
  {
    static_cast<CollisionNodeInstanceController*>(controller_.get())->onCollisionWith(_collider);
  }
}

bool CollisionNode::determineCollisionWithRect(AABB _rect)
{
  c2AABB colliderrect = aabbConversion(_rect);

  if(CollisionRectangle* rect = std::get_if<CollisionRectangle>(&shape_))
  {
    c2AABB myrect = aabbConversion(aabb_);
    return c2AABBtoAABB(myrect, colliderrect);
  }
  else if(CollisionCircle* circ = std::get_if<CollisionCircle>(&shape_))
  {
    c2Circle mycirc = circleConversion(circ);
    mycirc.p.x += pos_.x;
    mycirc.p.y -= pos_.y;
    return c2CircletoAABB(mycirc, colliderrect);
  }
  else 
    assert(0);
  // else if(CollisionCapsule* caps = std::get_if<CollisionCapsule>(&shape_))
  // {

  // }
  // else if(CollisionRay* ray = std::get_if<CollisionRay>(&shape_))
  // {

  // }


}

bool CollisionNode::determineCollisionWithCircle(Vec2 _center, float _r)
{
  return false;
}

bool CollisionNode::determineCollisionWithCapsule(Vec2 _apos, Vec2 _bpos, float _r)
{
  return false;
}

void CollisionNode::setCollisionRendering(bool _renderCollision)
{
  if(doRendering_ && !_renderCollision)
    Renderer::addSetPoints(points_to_render_.get());
  else if(!doRendering_)
    Renderer::removeSetPoints(points_to_render_.get());

  doRendering_ = _renderCollision;
}

void CollisionNode::movePos(const Vec2& _move)
{
  Node::movePos(_move);
  aabb_.bottom_left_ += _move;
  aabb_.top_right_ += _move;

  if(!doRendering_)
    return;

  for(auto& point : points_to_render_->points_)
  {
    point.x += _move.x;
    point.y += _move.y;
  }
}


/*----- CollisionNodeTemplate -----*/

CollisionNodeTemplate::CollisionNodeTemplate(const std::string& _name, CollisionShape _shape, std::function<CollisionNodeInstanceController*()> _controller_factory) : 
NodeTemplate(_name, _controller_factory), shape_(_shape)
{}

Node* CollisionNodeTemplate::createNode(NodeInstanceController* _controller)
{
  CollisionNode* n = new CollisionNode(default_name_, shape_, renderCollision, _controller);
  return n;
}
/*----- CollisionTemplate -----*/

/*----- CollisionNodeInstanceController -----*/

CollisionNode* CollisionNodeInstanceController::self() {return static_cast<CollisionNode*>(self_);}

void CollisionNodeInstanceController::onCollisionWith(CollisionNode* _collider) {}


/*----- CollisionNodeInstanceController -----*/
