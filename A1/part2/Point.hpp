#pragma once

class Point
{
public:
  int x, y, z;

  Point()
      : x(0), y(0), z(0) {}
  Point(int x, int y, int z)
      : x(x), y(y), z(z) {}

  int translate(int d, char axis)
  {
    switch (axis)
    {
    case 'x':
      x += d;
      return 0;
    case 'y':
      y += d;
      return 0;
    case 'z':
      z += d;
      return 0;
    default:
      return -2;
    }
    return -1;
  }
};