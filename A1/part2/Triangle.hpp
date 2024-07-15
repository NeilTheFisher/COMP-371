#include <cstdio>

#include "Point.hpp"

class Triangle
{
private:
  Point *vertex_1, *vertex_2, *vertex_3;

public:
  Triangle(Point *v1, Point *v2, Point *v3)
  {
    vertex_1 = v1;
    vertex_2 = v2;
    vertex_3 = v3;
  }

  ~Triangle()
  {
    delete vertex_1;
    delete vertex_2;
    delete vertex_3;
  }

  int translate(int d, char axis)
  {
    vertex_1->translate(d, axis);
    vertex_2->translate(d, axis);
    return vertex_3->translate(d, axis);
  }

  float calcArea()
  {
    float a = 0;
    a = vertex_1->x * (vertex_2->y - vertex_3->y) +
        vertex_2->x * (vertex_3->y - vertex_1->y) +
        vertex_3->x * (vertex_1->y - vertex_2->y);
    return a / 2;
  }

  void print()
  {
    printf("Triangle: (%d, %d, %d), (%d, %d, %d), (%d, %d, %d)\n",
           vertex_1->x, vertex_1->y, vertex_1->z,
           vertex_2->x, vertex_2->y, vertex_2->z,
           vertex_3->x, vertex_3->y, vertex_3->z);
  }
};