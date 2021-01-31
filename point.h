#ifndef POINT_H
#define POINT_H

#include<cmath>
#include<functional>

//================================================================
// Struct
//================================================================

struct point{
   int x,y;

   point(int x, int y): x(x), y(y){};
   point(const point &p): x(p.x), y(p.y){};
   point(): x(0), y(0){};

   point& operator+=(const point &p);
   point& operator-=(const point &p);
};

//================================================================
// Member functions
//================================================================

point& point::operator+=(const point &p){
   this->x += p.x;
   this->y += p.y;
   return *this;
}

point& point::operator-=(const point &p){
   this->x -= p.x;
   this->y -= p.y;
   return *this;
}

//================================================================
// Operators
//================================================================

bool operator==(const point &lhs, const point &rhs){
   return (lhs.x==rhs.x && lhs.y==rhs.y);
}

bool operator!=(const point &lhs, const point &rhs){
   return (lhs.x!=rhs.x || lhs.y!=rhs.y);
}

point operator+(const point &lhs, const point &rhs){
   return {lhs.x+rhs.x, lhs.y+rhs.y};
}

point operator-(const point &lhs, const point &rhs){
   return {lhs.x-rhs.x, lhs.y-rhs.y};
}

//================================================================
// Hashing function
//================================================================

namespace std {
   template <> struct hash<point> {
      typedef point argument_type;
      typedef std::size_t result_type;
      std::size_t operator()(const point& p) const noexcept {
         return std::hash<int>()(p.x ^ (p.y << 4));
      }
   };
}

//================================================================
// Other functions
//================================================================

// manhattan distance between two points
int manhattan(const point &p1, const point &p2){
    return std::abs(p2.x-p1.x) + std::abs(p2.y-p1.y);
}

#endif /* POINT_H */
