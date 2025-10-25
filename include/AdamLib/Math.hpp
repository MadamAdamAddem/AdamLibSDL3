#pragma once

namespace AdamLib
{

struct Vec2;
struct Vec2i;

struct Vec2
{
  Vec2(double _x = 0, double _y = 0) : x(_x), y(_y) {}

  double x;
  double y;

  double magnitude() const;
  static Vec2 normalize(const Vec2& vec);

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
  Vec2i(int _x = 0, int _y = 0) : x(_x), y(_y) {}

  int x;
  int y;

  int magnitude() const;
  static Vec2i normalize(const Vec2i& vec);

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