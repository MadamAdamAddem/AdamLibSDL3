#pragma once

namespace AdamLib
{

struct Vec2;
struct Vec2i;

struct Vec2
{
  Vec2(double _x, double _y);
  Vec2() = default;
  Vec2(const Vec2&) = default;

  double x;
  double y;

  bool null = true;

  double magnitude() const;
  Vec2& normalize();

  Vec2 getNormalized();


  Vec2 operator+(const Vec2& _other) const;
  Vec2 operator+(const Vec2i& _other) const;
  Vec2 operator-(const Vec2& _other) const;
  Vec2 operator-(const Vec2i& _other) const;
  Vec2 operator*(double _mult) const;
  Vec2 operator/(double _mult) const;

  Vec2& operator*=(double _mult);
  Vec2& operator/=(double _mult);
  Vec2& operator+=(const Vec2& _other);
  Vec2& operator+=(const Vec2i& _other);
  Vec2& operator-=(const Vec2& _other);
  Vec2& operator-=(const Vec2i& _other);
};

struct Vec2i
{
  Vec2i(int _x, int _y);
  Vec2i() = default;
  Vec2i(const Vec2i&) = default;

  int x;
  int y;

  bool null = true;

  double magnitude() const;
  Vec2i& normalize();

  Vec2i getNormalized();

  Vec2i operator+(const Vec2i& _other) const;
  Vec2i operator+(const Vec2& _other) const;
  Vec2i operator-(const Vec2i& _other) const;
  Vec2i operator-(const Vec2& _other) const;
  Vec2i operator*(double _mult) const;
  Vec2i operator/(double _mult) const;

  Vec2i& operator*=(double _mult);
  Vec2i& operator/=(double _mult);
  Vec2i& operator+=(const Vec2i& _other);
  Vec2i& operator+=(const Vec2& _other);
  Vec2i& operator-=(const Vec2i& _other);
  Vec2i& operator-=(const Vec2& _other);

};

struct Vec2li
{
  long x;
  long y;
};

struct Vec4
{
  double x;
  double y;
  double w;
  double h;
};

struct Vec4f
{
  float x;
  float y;
  float w;
  float h;
};

struct Vec4i
{
  int x;
  int y;
  int w;
  int h;
};

struct Vec4li
{
  long x;
  long y;
  long w;
  long h;
};

}