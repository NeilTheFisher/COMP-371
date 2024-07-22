#include <cstdio>

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
    if (vertex_1 != NULL && vertex_2 != NULL && vertex_3 != NULL)
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
    vertex_3->translate(d, axis);
  }

  float calcArea()
  {
    float a = 0;
    a = vertex_1->x * (vertex_2->y - vertex_3->y) +
        vertex_2->x * (vertex_3->y - vertex_1->y) +
        vertex_3->x * (vertex_1->y - vertex_2->y);
    return a / 2;
  }

  float calcArea()
  {
    float base = 0;
    float side = 0;
    float height = 0;

    base = math.abs(math.sqrt(
               (vertex_3.x - vertex_1.x) * (vertex_3.x - vertex_1.x) +
               (vertex_3.y - vertex_1.y) * (vertex_3.y - vertex_1.y) +
               (vertex_3.z - vertex_1.z) * (vertex_3.z - vertex_1.z))) /
           2;

    side = math.abs(math.sqrt(
        (vertex_2.x - vertex_3.x) * (vertex_2.x - vertex_3.x) +
        (vertex_2.y - vertex_3.y) * (vertex_2.y - vertex_3.y) +
        (vertex_2.z - vertex_3.z) * (vertex_2.z - vertex_3.z)));

    height = math.sqrt(side * side - base * base);
    return (base * height);
  }

  void print()
  {
    printf("Triangle: (%d, %d, %d), (%d, %d, %d), (%d, %d, %d)\n",
           vertex_1->x, vertex_1->y, vertex_1->z,
           vertex_2->x, vertex_2->y, vertex_2->z,
           vertex_3->x, vertex_3->y, vertex_3->z);
  }
};