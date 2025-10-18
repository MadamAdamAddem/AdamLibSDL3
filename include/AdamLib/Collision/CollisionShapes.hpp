#pragma once

#include <AdamLib/Defines.hpp>
#include <AdamLib/Math.hpp>


#ifdef DRAW_COLLISION 
#include "AdamLib/Core/Rendering.hpp"
#endif

namespace AdamLib
{

/*
  To Do:
    -Consider changing CollisionRay constructor to accept angle instead of direction normalized

*/



//! Contains bottom leftmost and top rightmost point of rectangle
struct AABB
{
  Vec2 bottom_left_;
  Vec2 top_right_;
};


//! Abstract Class defining the CollisionNode's internal shape
/*!
    Contains methods for drawing collision, when compiled with DRAW_COLLISION
*/
struct CollisionShape
{
  enum ShapeType
  {
    INVALID,
    RECTANGLE,
    CIRCLE,
    CAPSULE,
    RAY,
    POLYGON
  };
  ShapeType shapetype_{INVALID};

  #ifdef DRAW_COLLISION
  Renderer::SetOfPoints points_to_render_;
  virtual void updatePos(Vec2 _move) = 0;
  ~CollisionShape()
  {
    Renderer::removeSetPoints(&points_to_render_);
  }
  #endif

  AABB aabb_; //!<The bounding box for the shape, centered at 0,0
};




struct CollisionRectangle : public CollisionShape
{
  CollisionRectangle(const Vec2 _offset, const double _width, const double _height);

  #ifdef DRAW_COLLISION
  virtual void updatePos(Vec2 _pos) override;
  #endif


  Vec2 offset_; //!<Center of rectangle, relative to collisionnode
  Vec2 width_height_; //!<The width and height of rectangle, x = w,  y = h
};

struct CollisionCircle : public CollisionShape
{
  CollisionCircle(const Vec2 _offset, const float _r);

  #ifdef DRAW_COLLISION
  virtual void updatePos(Vec2 _pos) override;
  #endif



  Vec2 offset_; //!<Center of circle, relative to collisionnode
  float r_; //!<Radius
};

struct CollisionCapsule : public CollisionShape
{
  CollisionCapsule(const Vec2 _a_offset, const Vec2 _b_offset, const float _r);

  #ifdef DRAW_COLLISION
  virtual void updatePos(Vec2 _pos) override;
  #endif



  Vec2 a_offset_; //!<Circle a center, relative to collisionnode
  Vec2 b_offset_; //!<Circle b center, relative to collisionnode
  float r_; //!<Radius
};




struct CollisionRay : public CollisionShape
{
  CollisionRay(const Vec2 _offset, const Vec2 _direction_normalized, const float _len);

  #ifdef DRAW_COLLISION
  virtual void updatePos(Vec2 _pos) override;
  #endif
  
  Vec2 offset_; //!<The origin point of the ray, relative to collision node
  Vec2 direction_normalized_; //!<The direction of the ray, with positive y pointing downwards

  Vec2 p1; //!<Point 1 (Same as offset_)
  Vec2 p2; //!<Point 2 (Calculated with direction and length)
  
  float len_; //!<Length or magnitude of direction
};


//To Do: Implement
// struct CollisionPolygon : public CollisionShape
// {
//   CollisionPolygon();
//   AABB createAABB() override;

//   int numvert_;
//   Vec2 verts[MAX_POLYGON_VERTEXS];
//   Vec2 norms[MAX_POLYGON_VERTEXS];

// };

#define Rectangle(offset, width, height) std::bind([] (const Vec2 _offset, const double _width, const double _height) -> CollisionShape* { return new CollisionRectangle(_offset, _width, _height);}, offset, width, height)
#define Circle(offset, radius) std::bind([] (const Vec2 _offset, const float _r) -> CollisionShape* { return new CollisionCircle(_offset, _r);}, offset, radius)
#define Capsule(a_offset, b_offset, radius) std::bind([] (const Vec2 _a_offset, const Vec2 _b_offset, const float _r) -> CollisionShape* { return new CollisionCapsule(_a_offset, _b_offset, _r);}, a_offset, b_offset, radius)
#define Ray(offset, direction, length) std::bind([] (const Vec2 _offset, const Vec2 _direction, const float _len) -> CollisionShape* { return new CollisionRay(_offset, _direction, _len);}, offset, direction, length)


}