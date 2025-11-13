#pragma once
#include <concepts>
#include <cmath>
#include <algorithm>
#include <functional>

namespace AdamLib
{

template <typename T>
concept ArithmeticChainable = requires (T a, T b)
{
  {a + b} -> std::convertible_to<T>;
  {a - b} -> std::convertible_to<T>;
  {a * b} -> std::convertible_to<T>;
  {a / b} -> std::convertible_to<T>;

  {a += b} -> std::same_as<T&>;
  {a -= b} -> std::same_as<T&>;
  {a *= b} -> std::same_as<T&>;
  {a /= b} -> std::same_as<T&>;
};

template <typename T>
concept SquareRootable = requires (T a)
{
  {std::sqrt(a)} -> std::convertible_to<T>;
};


template <ArithmeticChainable T, int Size> requires std::default_initializable<T>
struct Vec
{
  T item[Size];
  bool nullstate;

  Vec operator+(const Vec& _other) const
  {
    Vec retval;
    std::transform(item, item + Size, _other.item, retval.item, std::plus<>{});
    return retval;
  }
  Vec operator-(const Vec& _other) const
  {
    Vec retval;
    std::transform(item, item + Size, _other.item, retval.item, std::minus<>{});
    return retval;
  }
  Vec operator*(const Vec& _other) const
  {
    Vec retval;
    std::transform(item, item + Size, _other.item, retval.item, std::multiplies<>{});
    return retval;
  }
  Vec operator/(const Vec& _other) const
  {
    Vec retval;
    std::transform(item, item + Size, _other.item, retval.item, std::divides<>{});
    return retval;
  }


  Vec& operator+=(const Vec& _other);
  Vec& operator-=(const Vec& _other);
  Vec operator*=(const Vec& _other);
  Vec operator/=(const Vec& _other);

};

template<typename _Tp, typename... _Up> //shamelessly stolen from the GNU ISO C++ library to support CTAD because I was too stupid to do it myself, thanks guys
Vec(_Tp, _Up...) -> Vec<std::enable_if_t<(std::is_same_v<_Tp, _Up> && ...), _Tp>, 1 + sizeof...(_Up)>;






}