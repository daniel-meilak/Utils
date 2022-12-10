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

   point_t(Int x, Int y): x(x), y(y){};
   point_t(const point_t<Int>& p) = default;
   point_t(): x(0), y(0){};

   // spaceship operator defines "==","!=",">","<",">=","<="
   auto operator<=>(const point_t&) const = default;

   point_t& operator+=(const point_t& p);
   point_t& operator-=(const point_t& p);
   point_t& operator*=(const Int& i);
   point_t& operator/=(const Int& i);
};
using point = point_t<int>;

//================================================================
// Member functions
//================================================================

template <typename Int>
point_t<Int> &point_t<Int>::operator+=(const point_t &p){
   this->x += p.x;
   this->y += p.y;
   return *this;
}

template <typename Int>
point_t<Int> &point_t<Int>::operator-=(const point_t &p){
   this->x -= p.x;
   this->y -= p.y;
   return *this;
}

template <typename Int>
point_t<Int> &point_t<Int>::operator*=(const Int &i){
   this->x *= i;
   this->y *= i;
   return *this;
}

template <typename Int>
point_t<Int> &point_t<Int>::operator/=(const Int &i){
   this->x /= i;
   this->y /= i;
   return *this;
}

//================================================================
// Operators
//================================================================

template <typename Int>
point_t<Int> operator+(const point_t<Int> &lhs, const point_t<Int> &rhs){
   return {lhs.x+rhs.x, lhs.y+rhs.y};
}

template <typename Int>
point_t<Int> operator-(const point_t<Int> &lhs, const point_t<Int> &rhs){
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
