#include <AdamLib/Collision/CollisionShapes.hpp>
#include "../Core/RendererInternal.hpp"
#include <algorithm>
#include <memory>

using namespace AdamLib;


CollisionShape::CollisionShape() : points_to_render_(std::make_unique<Renderer::SetOfPoints>())
{

}

CollisionShape::~CollisionShape()
{
  Renderer::removeSetPoints(points_to_render_.get());
}

void CollisionShape::setVisibility(bool doRendering)
{
  if(doRendering && !renderCollision)
    Renderer::addSetPoints(points_to_render_.get());
  else if(!doRendering)
    Renderer::removeSetPoints(points_to_render_.get());

  renderCollision = doRendering;
}


/*----- Rectangle -----*/

CollisionRectangle::CollisionRectangle(const Vec2 _offset, const double _width, const double _height) : offset_(_offset), width_height_({_width, _height})
{
  aabb_ = {{offset_.x - width_height_.x/2, offset_.y + width_height_.y/2},{offset_.x + width_height_.x/2, offset_.y - width_height_.y/2}};
  shapetype_ = RECTANGLE;

  points_to_render_->points_.resize(5);
}

void CollisionRectangle::updatePos(Vec2 _pos)
{
  if(!renderCollision)
    return;

  points_to_render_->points_[0].x = aabb_.bottom_left_.x + _pos.x;
  points_to_render_->points_[0].y = aabb_.bottom_left_.y + _pos.y;

  points_to_render_->points_[1].x = aabb_.bottom_left_.x + _pos.x;
  points_to_render_->points_[1].y = aabb_.top_right_.y + _pos.y;

  points_to_render_->points_[2].x = aabb_.top_right_.x + _pos.x;
  points_to_render_->points_[2].y = aabb_.top_right_.y + _pos.y;

  points_to_render_->points_[3].x = aabb_.top_right_.x + _pos.x;
  points_to_render_->points_[3].y = aabb_.bottom_left_.y + _pos.y;

  points_to_render_->points_[4] = points_to_render_->points_[0];
}


/*----- Rectangle -----*/



/*----- Circle -----*/

CollisionCircle::CollisionCircle(const Vec2 _offset, const float _r) : offset_(_offset), r_(_r)
{

  aabb_ = {{offset_.x - r_, offset_.y + r_}, {offset_.x + r_, offset_.y - r_}};
  shapetype_ = CIRCLE;


  points_to_render_->points_.resize(9);

}


void CollisionCircle::updatePos(Vec2 _pos)
{

}


/*----- Circle -----*/



/*----- Capsule -----*/

//TODO: Finish this shit
CollisionCapsule::CollisionCapsule(const Vec2 _a_offset, const Vec2 _b_offset, float _r) : a_offset_(_a_offset), b_offset_(_b_offset), r_(_r)
{
  double rightmost = std::max(a_offset_.x, b_offset_.x) + r_;
  double leftmost = std::min(a_offset_.x, b_offset_.x) - r_;

  //increased y is lower height, origin is top left
  double upmost = std::min(a_offset_.y, b_offset_.y) - r_;
  double downmost = std::max(a_offset_.y, a_offset_.y) + r_;

  aabb_ = {{leftmost, downmost}, {rightmost, upmost}};
  shapetype_ = CAPSULE;

  points_to_render_->points_.resize(11);
}

void CollisionCapsule::updatePos(Vec2 _pos)
{
  if(!renderCollision)
    return;

}



/*----- Capsule -----*/


//To Do: Implement Polygon

/*----- Ray -----*/

CollisionRay::CollisionRay(const Vec2 _offset, const Vec2 _direction, const float _len) :
offset_(_offset), direction_normalized_(_direction), len_(_len)
{
  Vec2 endpoint = {direction_normalized_.x * len_ + offset_.x, direction_normalized_.y * len_ + offset_.y};
  p1 = offset_;
  p2 = endpoint;

  double leftmost = std::min(p1.x, p2.x);
  double rightmost = std::max(p1.x, p2.x);

  //increased y is lower height, origin is top left
  double upmost = std::min(p1.y, p2.y);
  double downmost = std::max(p1.y, p2.y);

  aabb_ = {{leftmost, downmost}, {rightmost, upmost}};
  shapetype_ = RAY;

  points_to_render_->points_.resize(2);
}

void CollisionRay::updatePos(Vec2 _pos)
{
  if(!renderCollision)
    return;

  points_to_render_->points_[0].x = p1.x + _pos.x;
  points_to_render_->points_[0].y = p1.y + _pos.y;

  points_to_render_->points_[1].x = p2.x + _pos.x;
  points_to_render_->points_[1].y = p2.y + _pos.y;

}


/*----- Ray -----*/