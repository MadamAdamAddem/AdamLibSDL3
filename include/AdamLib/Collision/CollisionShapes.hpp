#pragma once

#include <AdamLib/Defines.hpp>
#include <AdamLib/Math.hpp>


#ifdef DRAW_COLLISION 
#include "AdamLib/Core/Rendering.hpp"
#endif

namespace AdamLib
{

struct AABB
{
  Vec2 bottom_left_;
  Vec2 top_right_;
};


class CollisionRectangle;
class CollisionCapsule;
class CollisionCircle;

//class CollisionRay;
//class CollisionPolygon;

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


  // virtual bool determineCollisionWith(CollisionRay* _rect) = 0;
  // virtual bool determineCollisionWith(CollisionPolygon* _rect) = 0;


  AABB aabb_;
};




struct CollisionRectangle : public CollisionShape
{
  CollisionRectangle(const Vec2 _offset, const Vec2 _width_height);

  #ifdef DRAW_COLLISION
  virtual void updatePos(Vec2 _pos) override;
  #endif


  Vec2 offset_; //center of rectangle, relative to collisionnode
  Vec2 width_height_;
};

struct CollisionCircle : public CollisionShape
{
  CollisionCircle(const Vec2 _offset, const float _r);

  #ifdef DRAW_COLLISION
  virtual void updatePos(Vec2 _pos) override;
  #endif



  Vec2 offset_; //center of circle, relative to collisionnode
  float r_;
};

struct CollisionCapsule : public CollisionShape
{
  CollisionCapsule(const Vec2 _a_offset, const Vec2 _b_offset, const float _r);

  #ifdef DRAW_COLLISION
  virtual void updatePos(Vec2 _pos) override;
  #endif



  Vec2 a_offset_; //circle a center, relative to collisionnode
  Vec2 b_offset_; //circle b center, relative to collisionnode
  float r_;
};



struct CollisionRay : public CollisionShape
{
  CollisionRay(const Vec2 _offset, const Vec2 _direction, const float _len);

  #ifdef DRAW_COLLISION
  virtual void updatePos(Vec2 _pos) override;
  #endif
  
  Vec2 offset_; //offset relative to collisionnode
  Vec2 direction_; //normalized

  Vec2 p1;
  Vec2 p2;
  
  float len_;
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


}