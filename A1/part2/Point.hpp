#pragma once

class Point
{
public:
  int x, y, z;

  Point()
      : x(0), y(0), z(0) {}
  Point(int x, int y, int z)
      : x(x), y(y), z(z) {}

  ~Point() {}

  int translate(int d, char axis)
  {
    // if d is not an integer, return -2 but the first parameter is always garanteed to be an int
    if (std::floor(d) != d)
    {
      return -2;
    }

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
      return -1;
    }
  }
};