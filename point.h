#pragma once

#include<cmath>
#include<compare> // C++20
#include<functional>

//================================================================
// Struct
//================================================================

template <typename Int = int>
struct point_t{
   Int x,y;

   constexpr point_t(Int x, Int y): x(x), y(y){};
   constexpr point_t(const point_t<Int>& p) = default;
   constexpr point_t(): x(0), y(0){};

   // spaceship operator defines "==","!=",">","<",">=","<="
   constexpr auto operator<=>(const point_t&) const = default;

   constexpr point_t& operator+=(const point_t& p);
   constexpr point_t& operator-=(const point_t& p);
   constexpr point_t& operator*=(const Int& i);
   constexpr point_t& operator/=(const Int& i);

   // move in direction functions
   constexpr point_t up(Int i = 1) const;
   constexpr point_t down(Int i = 1) const;
   constexpr point_t left(Int i = 1) const;
   constexpr point_t right(Int i = 1) const;
};
using point = point_t<int>;

//================================================================
// Member functions
//================================================================

template <typename Int>
constexpr point_t<Int> &point_t<Int>::operator+=(const point_t &p){
   this->x += p.x;
   this->y += p.y;
   return *this;
}

template <typename Int>
constexpr point_t<Int> &point_t<Int>::operator-=(const point_t &p){
   this->x -= p.x;
   this->y -= p.y;
   return *this;
}

template <typename Int>
constexpr point_t<Int> &point_t<Int>::operator*=(const Int &i){
   this->x *= i;
   this->y *= i;
   return *this;
}

template <typename Int>
constexpr point_t<Int> &point_t<Int>::operator/=(const Int &i){
   this->x /= i;
   this->y /= i;
   return *this;
}

//================================================================
// Operators
//================================================================

template <typename Int>
constexpr point_t<Int> operator+(const point_t<Int> &lhs, const point_t<Int> &rhs){
   return {lhs.x+rhs.x, lhs.y+rhs.y};
}

template <typename Int>
constexpr point_t<Int> operator-(const point_t<Int> &lhs, const point_t<Int> &rhs){
   return {lhs.x-rhs.x, lhs.y-rhs.y};
}

//================================================================
// Hashing function
//================================================================

namespace std {
   template <typename Int>
   struct hash<point_t<Int>> {

      std::size_t operator()(const point_t<Int>& p) const noexcept {
         return std::hash<Int>()(p.x ^ (p.y << 4));
      }
   };
}

//================================================================
// move in direction functions
//================================================================

template <typename Int>
constexpr point_t<Int> point_t<Int>::up(Int i) const{
   return {this->x, this->y-i};
}

template <typename Int>
constexpr point_t<Int> point_t<Int>::down(Int i) const{
   return {this->x, this->y+i};
}

template <typename Int>
constexpr point_t<Int> point_t<Int>::left(Int i) const{
   return {this->x-i, this->y};
}

template <typename Int>
constexpr point_t<Int> point_t<Int>::right(Int i) const{
   return {this->x+i, this->y};
}

//================================================================
// Other functions
//================================================================

// manhattan distance between two point_ts
template <typename Int>
Int manhattan(const point_t<Int> &p1, const point_t<Int> &p2){
   return std::abs(p2.x-p1.x) + std::abs(p2.y-p1.y);
}

// chebyshev distance between two point_ts (diagonal is equal to vert/hori)
template <typename Int>
Int chebyshev(const point_t<Int> &p1, const point_t<Int> &p2){
   return std::max(std::abs(p2.x-p1.x), std::abs(p2.y-p1.y));
}
