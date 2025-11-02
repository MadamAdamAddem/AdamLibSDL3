#include <AdamLib/Math.hpp>
#include <cmath>



using namespace AdamLib;

Vec2::Vec2(double _x, double _y) : x(_x), y(_y) {null = false;}

double Vec2::magnitude() const {if(null) return 0; return std::sqrt(x*x + y*y);}

Vec2& Vec2::normalize() 
{
  if(null)
    return *this;

  double mag = magnitude();
  if(mag == 0)
    return *this;

  *this /= mag;
  return *this;
}

Vec2 Vec2::getNormalized()
{
  return Vec2(*this).normalize();
}

Vec2 Vec2::operator+(const Vec2& _other) const { if(null || _other.null) return Vec2(); return Vec2(x + _other.x, y + _other.y); }

Vec2 Vec2::operator+(const Vec2i& _other) const { if(null || _other.null) return Vec2(); return Vec2(x + _other.x, y + _other.y); }

Vec2 Vec2::operator-(const Vec2& _other) const { if(null || _other.null) return Vec2(); return Vec2(x - _other.x, y - _other.y); }

Vec2 Vec2::operator-(const Vec2i& _other) const { if(null || _other.null) return Vec2(); return Vec2(x - _other.x, y - _other.y); }

Vec2 Vec2::operator*(double _mult) const { if(null) return Vec2(); return Vec2(x * _mult, y * _mult); }

Vec2 Vec2::operator/(double _div) const { if(null) return Vec2(); return Vec2(x / _div, y / _div); }



Vec2& Vec2::operator*=(double _mult) { if(!null) x *= _mult; y *= _mult; return *this; }

Vec2& Vec2::operator/=(double _mult) { if(!null) x /= _mult; y /= _mult; return *this; }

Vec2& Vec2::operator+=(const Vec2& _other) { if(!null && !_other.null) x += _other.x; y += _other.y; return *this; }

Vec2& Vec2::operator+=(const Vec2i& _other) { if(!null && !_other.null) x += _other.x; y += _other.y; return *this; }

Vec2& Vec2::operator-=(const Vec2& _other) { if(!null && !_other.null) x -= _other.x; y -= _other.y; return *this; }

Vec2& Vec2::operator-=(const Vec2i& _other) { if(!null && !_other.null) x -= _other.x; y -= _other.y; return *this; }



Vec2i::Vec2i(int _x, int _y) : x(_x), y(_y) {null = false;}

double Vec2i::magnitude() const {if(null) return 0; else return std::sqrt(x*x + y*y);}

Vec2i& Vec2i::normalize() 
{
  if(null)
    return *this;

  double mag = magnitude();
  if(mag == 0)
    return *this;

  *this /= mag;
  return *this;
}

Vec2i Vec2i::getNormalized()
{
  return Vec2i(*this).normalize();
}

Vec2i Vec2i::operator+(const Vec2i& _other) const { if(null || _other.null) return Vec2i(); return Vec2i(x + _other.x, y + _other.y); }

Vec2i Vec2i::operator+(const Vec2& _other) const { if(null || _other.null) return Vec2i(); return Vec2i(x + _other.x, y + _other.y); }

Vec2i Vec2i::operator-(const Vec2i& _other) const { if(null || _other.null) return Vec2i(); return Vec2i(x - _other.x, y - _other.y); }

Vec2i Vec2i::operator-(const Vec2& _other) const { if(null || _other.null) return Vec2i(); return Vec2i(x - _other.x, y - _other.y); }

Vec2i Vec2i::operator*(double _mult) const {  if(null) return Vec2i(); return Vec2i(x * _mult, y * _mult); }

Vec2i Vec2i::operator/(double _mult) const { if(null) return Vec2i(); return Vec2i(x / _mult, y / _mult); }



Vec2i& Vec2i::operator*=(double _mult) { if(!null) x *= _mult; y *= _mult; return *this; }

Vec2i& Vec2i::operator/=(double _mult) { if(!null) x /= _mult; y /= _mult; return *this; }

Vec2i& Vec2i::operator+=(const Vec2i& _other) {  if(!null && !_other.null) x += _other.x; y += _other.y; return *this; }

Vec2i& Vec2i::operator+=(const Vec2& _other) {  if(!null && !_other.null) x += _other.x; y += _other.y; return *this; }

Vec2i& Vec2i::operator-=(const Vec2i& _other) { if(!null && !_other.null) x -= _other.x; y -= _other.y; return *this; }

Vec2i& Vec2i::operator-=(const Vec2& _other) {  if(!null && !_other.null) x -= _other.x; y -= _other.y; return *this; }