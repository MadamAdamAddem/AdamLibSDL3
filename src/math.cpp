#include <AdamLib/Math.hpp>
#include <cmath>



using namespace AdamLib;

double Vec2::magnitude() const {return std::sqrt(x*x + y*y);}

Vec2 Vec2::normalize(const Vec2& vec) 
{
  double mag = vec.magnitude();
  if(mag == 0)
    return vec;
  return vec / mag;

}

Vec2 Vec2::operator+(const Vec2& _other) const { return Vec2(x + _other.x, y + _other.y); }

Vec2 Vec2::operator+(const Vec2i& _other) const { return Vec2(x + _other.x, y + _other.y); }

Vec2 Vec2::operator-(const Vec2& _other) const { return Vec2(x - _other.x, y - _other.y); }

Vec2 Vec2::operator-(const Vec2i& _other) const { return Vec2(x - _other.x, y - _other.y); }



Vec2 Vec2::operator*(double _mult) const { return Vec2(x * _mult, y * _mult); }

Vec2 Vec2::operator/(double _div) const { return Vec2(x / _div, y / _div); }

Vec2& Vec2::operator*=(double _mult) { x *= _mult; y *= _mult; return *this; }

Vec2& Vec2::operator/=(double _mult) { x /= _mult; y /= _mult; return *this; }

Vec2& Vec2::operator+=(const Vec2& _other) { x += _other.x; y += _other.y; return *this; }

Vec2& Vec2::operator+=(const Vec2i& _other) { x += _other.x; y += _other.y; return *this; }

Vec2& Vec2::operator-=(const Vec2& _other) { x -= _other.x; y -= _other.y; return *this; }

Vec2& Vec2::operator-=(const Vec2i& _other) { x -= _other.x; y -= _other.y; return *this; }



int Vec2i::magnitude() const {return std::sqrt(x*x + y*y);}

Vec2i Vec2i::normalize(const Vec2i& vec) 
{ 
  int mag = vec.magnitude();
  if(mag == 0)
    return vec;
  return vec / mag;
}

Vec2i Vec2i::operator+(const Vec2i& _other) const { return Vec2i(x + _other.x, y + _other.y); }

Vec2i Vec2i::operator+(const Vec2& _other) const { return Vec2i(x + _other.x, y + _other.y); }

Vec2i Vec2i::operator-(const Vec2i& _other) const { return Vec2i(x - _other.x, y - _other.y); }

Vec2i Vec2i::operator-(const Vec2& _other) const { return Vec2i(x - _other.x, y - _other.y); }

Vec2i Vec2i::operator*(double _mult) const { return Vec2i(x * _mult, y * _mult); }

Vec2i Vec2i::operator/(double _mult) const { return Vec2i(x / _mult, y / _mult); }



Vec2i& Vec2i::operator*=(double _mult) { x *= _mult; y *= _mult; return *this; }

Vec2i& Vec2i::operator/=(double _mult) { x /= _mult; y /= _mult; return *this; }

Vec2i& Vec2i::operator+=(const Vec2i& _other) { x += _other.x; y += _other.y; return *this; }

Vec2i& Vec2i::operator+=(const Vec2& _other) { x += _other.x; y += _other.y; return *this; }

Vec2i& Vec2i::operator-=(const Vec2i& _other) { x -= _other.x; y -= _other.y; return *this; }

Vec2i& Vec2i::operator-=(const Vec2& _other) { x -= _other.x; y -= _other.y; return *this; }