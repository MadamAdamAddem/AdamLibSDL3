#include <AdamLib/Collision/CollisionShapes.hpp>
#include <algorithm>

using namespace AdamLib;




/*----- Rectangle -----*/

CollisionRectangle::CollisionRectangle(const Vec2 _offset, const Vec2 _width_height) : offset_(_offset), width_height_(_width_height)
{
  aabb_ = {{offset_.x - width_height_.x/2, offset_.y + width_height_.y/2},{offset_.x + width_height_.x/2, offset_.y - width_height_.y/2}};

  #ifdef DRAW_COLLISION
  points_to_render_.points_.reserve(5);
  points_to_render_.points_.resize(5);

  Renderer::addSetPoints(&points_to_render_);
  #endif
}

#ifdef DRAW_COLLISION
void CollisionRectangle::updatePos(Vec2 _pos)
{
  points_to_render_.points_[0].x = aabb_.bottom_left_.x + _pos.x;
  points_to_render_.points_[0].y = aabb_.bottom_left_.y + _pos.y;

  points_to_render_.points_[1].x = aabb_.bottom_left_.x + _pos.x;
  points_to_render_.points_[1].y = aabb_.top_right_.y + _pos.y;

  points_to_render_.points_[2].x = aabb_.top_right_.x + _pos.x;
  points_to_render_.points_[2].y = aabb_.top_right_.y + _pos.y;

  points_to_render_.points_[3].x = aabb_.top_right_.x + _pos.x;
  points_to_render_.points_[3].y = aabb_.bottom_left_.y + _pos.y;

  points_to_render_.points_[4] = points_to_render_.points_[0];
}
#endif

/*----- Rectangle -----*/



/*----- Circle -----*/

CollisionCircle::CollisionCircle(Vec2 _offset, float _r) : offset_(_offset), r_(_r)
{

  aabb_ = {{offset_.x - r_, offset_.y + r_}, {offset_.x + r_, offset_.y - r_}};

  #ifdef DRAW_COLLISION
  points_to_render_.points_.reserve(8);
  points_to_render_.points_.resize(8);

  Renderer::addSetPoints(&points_to_render_);
  #endif
}


#ifdef DRAW_COLLISION
void CollisionCircle::updatePos(Vec2 _move)
{

}
#endif

/*----- Circle -----*/



/*----- Capsule -----*/

//TODO: Finish this shit
CollisionCapsule::CollisionCapsule(Vec2& _a_offset, Vec2& _b_offset, float _r) : a_offset_(_a_offset), b_offset_(_b_offset), r_(_r)
{
  double rightmost = std::max(a_offset_.x, b_offset_.x) + r_;
  double leftmost = std::min(a_offset_.x, b_offset_.x) - r_;
  aabb_.bottom_left_.x = leftmost;
  aabb_.top_right_.x = rightmost;

  //increased y is lower height, origin is top left
  double upmost = std::min(a_offset_.y, b_offset_.y) - r_;
  double downmost = std::max(a_offset_.y, a_offset_.y) + r_;
  aabb_.bottom_left_.y = downmost;
  aabb_.top_right_.y = upmost;

  #ifdef DRAW_COLLISION
  points_to_render_.points_.reserve(10);
  points_to_render_.points_.resize(10);

  Renderer::addSetPoints(&points_to_render_);
  #endif
}

#ifdef DRAW_COLLISION
void CollisionCapsule::updatePos(Vec2 _move)
{
  
}
#endif

/*----- Capsule -----*/


//To Do: Implement Ray and Polygon

// /*----- Ray -----*/

// AABB CollisionRay::createAABB()
// {
//   return {{0,0}, {0,0}};
// }

// /*----- Ray -----*/