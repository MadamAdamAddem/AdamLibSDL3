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


struct CollisionShape
{
  #ifdef DRAW_COLLISION
  Renderer::SetOfPoints points_to_render_;
  virtual void updatePos(Vec2 _move) = 0;
  ~CollisionShape()
  {
    Renderer::removeSetPoints(&points_to_render_);
  }
  #endif

  AABB aabb_;
};




struct CollisionRectangle : public CollisionShape
{
  CollisionRectangle(const Vec2 _offset, const Vec2 _width_height);

  #ifdef DRAW_COLLISION
  virtual void updatePos(Vec2 _move) override;
  #endif

  Vec2 offset_; //center of rectangle, relative to collisionnode
  Vec2 width_height_;
};

struct CollisionCircle : public CollisionShape
{
  CollisionCircle(Vec2 _offset, float _r);

  #ifdef DRAW_COLLISION
  virtual void updatePos(Vec2 _move) override;
  #endif

  Vec2 offset_; //center of circle, relative to collisionnode
  float r_;
};

struct CollisionCapsule : public CollisionShape
{
  CollisionCapsule(Vec2& _a_offset, Vec2& _b_offset, float _r);

  #ifdef DRAW_COLLISION
  virtual void updatePos(Vec2 _move) override;
  #endif

  Vec2 a_offset_; //circle a center, relative to collisionnode
  Vec2 b_offset_; //circle b center, relative to collisionnode
  float r_;
};


//To Do: Finish this shit

// struct CollisionRay : public CollisionShape
// {
//   CollisionRay();
//   AABB createAABB() override;
  
//   Vec2 offset_; //offset relative to collisionnode
//   Vec2 direction_; //normalized
//   float len_;
// };

// struct CollisionPolygon : public CollisionShape
// {
//   CollisionPolygon();
//   AABB createAABB() override;

//   int numvert_;
//   Vec2 verts[MAX_POLYGON_VERTEXS];
//   Vec2 norms[MAX_POLYGON_VERTEXS];

// };


}