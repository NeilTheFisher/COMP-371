#include <cstdio>
#include <cmath>
#include "Point.hpp"

class Triangle
{
private:
  Point *vertex_1, *vertex_2, *vertex_3;

public:
  Triangle()
      : vertex_1(nullptr), vertex_2(nullptr), vertex_3(nullptr) {}

  Triangle(Point *v1, Point *v2, Point *v3)
  {
    vertex_1 = v1;
    vertex_2 = v2;
    vertex_3 = v3;
  }

  ~Triangle()
  {
    if (vertex_1 && vertex_2 && vertex_3)
    {
      delete vertex_1;
      delete vertex_2;
      delete vertex_3;
    }
  }

  int translate(int d, char axis)
  {
    vertex_1->translate(d, axis);
    vertex_2->translate(d, axis);
    return vertex_3->translate(d, axis);
  }

  // float calcArea()
  // {
  //   float a = 0;
  //   a = vertex_1->x * (vertex_2->y - vertex_3->y) +
  //       vertex_2->x * (vertex_3->y - vertex_1->y) +
  //       vertex_3->x * (vertex_1->y - vertex_2->y);
  //   return a / 2;
  // }

  // float calcArea()
  // {
  //   float base = std::sqrt(std::abs(
  //                    (vertex_3->x - vertex_1->x) * (vertex_3->x - vertex_1->x) +
  //                    (vertex_3->y - vertex_1->y) * (vertex_3->y - vertex_1->y) +
  //                    (vertex_3->z - vertex_1->z) * (vertex_3->z - vertex_1->z))) /
  //                2;

  //   float side = std::sqrt(std::abs(
  //       (vertex_2->x - vertex_3->x) * (vertex_2->x - vertex_3->x) +
  //       (vertex_2->y - vertex_3->y) * (vertex_2->y - vertex_3->y) +
  //       (vertex_2->z - vertex_3->z) * (vertex_2->z - vertex_3->z)));

  //   float height = std::sqrt(side * side - base * base);
  //   return (base * height);
  // }

  float calcArea()
  {
    int x1 = vertex_1->x;
    int y1 = vertex_1->y;
    int z1 = vertex_1->z;
    int x2 = vertex_2->x;
    int y2 = vertex_2->y;
    int z2 = vertex_2->z;
    int x3 = vertex_3->x;
    int y3 = vertex_3->y;
    int z3 = vertex_3->z;

    return std::sqrt(
               std::pow((x2 * y1 - x3 * y1 - x1 * y2 + x3 * y2 + x1 * y3 - x2 * y3), 2) +
               std::pow((x2 * z1 - x3 * z1 - x1 * z2 + x3 * z2 + x1 * z3 - x2 * z3), 2) +
               std::pow((y2 * z1 - y3 * z1 - y1 * z2 + y3 * z2 + y1 * z3 - y2 * z3), 2)) /
           2;
  }

  void print()
  {
    printf("Triangle: (%d, %d, %d), (%d, %d, %d), (%d, %d, %d)\n",
           vertex_1->x, vertex_1->y, vertex_1->z,
           vertex_2->x, vertex_2->y, vertex_2->z,
           vertex_3->x, vertex_3->y, vertex_3->z);
  }
};