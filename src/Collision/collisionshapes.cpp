#include <AdamLib/Collision/CollisionShapes.hpp>


#include <SDL3/SDL_rect.h>


using namespace AdamLib;


/*----- Rectangle -----*/

CollisionRectangle::CollisionRectangle(const Vec2& _center, const double _width, const double _height) : 
center_(_center), width_height_({_width, _height})
{
}

/*----- Rectangle -----*/



/*----- Circle -----*/

CollisionCircle::CollisionCircle(const Vec2& _center, const double _r) : 
center_(_center), r_(_r)
{

}



/*----- Circle -----*/



/*----- Capsule -----*/

CollisionCapsule::CollisionCapsule(const Vec2& _a_center, const Vec2& _b_center, double _r) : 
a_center_(_a_center), b_center_(_b_center), r_(_r)
{

}


/*----- Capsule -----*/


//To Do: Implement Polygon

/*----- Ray -----*/

CollisionRay::CollisionRay(const Vec2& _center, const Vec2& _direction, const double _len) :
p1_(_center), p2_(_direction.x * _len + _center.x, _direction.y * _len + _center.y), direction_normalized_(_direction), len_(_len)
{

}

/*----- Ray -----*/





