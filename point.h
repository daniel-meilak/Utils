#pragma once

#include<cmath>
#include<compare> // C++20
#include<functional>

//================================================================
// Struct
//================================================================

template< typename Int = int >
struct point{
   Int x,y;

   point(Int x, Int y): x(x), y(y){};
   point(const point<Int> &p): x(p.x), y(p.y){};
   point(): x(0), y(0){};

   // spaceship operator defines "==","!=",">","<",">=","<="
   auto operator<=>(const point&) const = default;

   point& operator+=(const point &p);
   point& operator-=(const point &p);
   point& operator*=(const Int   &i);
   point& operator/=(const Int   &i);
};

//================================================================
// Member functions
//================================================================

template< typename Int >
point<Int> &point<Int>::operator+=(const point &p){
   this->x += p.x;
   this->y += p.y;
   return *this;
}

template< typename Int >
point<Int> &point<Int>::operator-=(const point &p){
   this->x -= p.x;
   this->y -= p.y;
   return *this;
}

template< typename Int >
point<Int> &point<Int>::operator*=(const Int &i){
   this->x *= i;
   this->y *= i;
   return *this;
}

template< typename Int >
point<Int> &point<Int>::operator/=(const Int &i){
   this->x /= i;
   this->y /= i;
   return *this;
}

//================================================================
// Operators
//================================================================

template< typename Int >
point<Int> operator+(const point<Int> &lhs, const point<Int> &rhs){
   return {lhs.x+rhs.x, lhs.y+rhs.y};
}

template< typename Int >
point<Int> operator-(const point<Int> &lhs, const point<Int> &rhs){
   return {lhs.x-rhs.x, lhs.y-rhs.y};
}

//================================================================
// Hashing function
//================================================================

namespace std {
   template < typename Int > struct hash<point<Int>> {
      typedef point<Int> argument_type;
      typedef std::size_t result_type;
      std::size_t operator()(const point<Int>& p) const noexcept {
         return std::hash<Int>()(p.x ^ (p.y << 4));
      }
   };
}

//================================================================
// Other functions
//================================================================

// manhattan distance between two points
template< typename Int >
Int manhattan(const point<Int> &p1, const point<Int> &p2){
    return std::abs(p2.x-p1.x) + std::abs(p2.y-p1.y);
}
