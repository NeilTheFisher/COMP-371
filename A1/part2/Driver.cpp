#include <cstdio>

#include "Triangle.hpp"
#include "Point.hpp"

class Driver
{
private:
  Triangle *triangle;

public:
  ~Driver()
  {
    delete triangle;
  }

  void createTriangle()
  {
    Point *p1 = new Point(1, 2, 3);
    Point *p2 = new Point(4, 5, 6);
    Point *p3 = new Point(7, 8, 9);
    triangle = new Triangle(p1, p2, p3);
  }

  Point inputTranslateTriangle()
  {
    Point translation;
    printf("\n\nInput translation distances for each axis:\n");
    printf("Enter x: ");
    scanf("%d", &translation.x);
    printf("\nEnter y: ");
    scanf("%d", &translation.y);
    printf("\nEnter z: ");
    scanf("%d", &translation.z);

    return translation;
  }

  void translateTriangle(int d, char axis)
  {
    triangle->translate(d, axis);
  }

  void printTriangle()
  {
    triangle->print();
  }
};

int main()
{
  Driver d;

  d.createTriangle();

  d.printTriangle();

  Point translation = d.inputTranslateTriangle();
  d.translateTriangle(translation.x, 'x');
  d.translateTriangle(translation.y, 'y');
  d.translateTriangle(translation.z, 'z');

  d.printTriangle();
}