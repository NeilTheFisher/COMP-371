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
    int num1;
    int num2;
    int num3;
    printf("Select the x,y,z coordinates for the first point eg.'x y z': ");
    scanf("%d %d %d", &num1, &num2, &num3);
    Point *p1 = new Point(num1, num2, num3);
    printf("Select the x,y,z coordinates for the second point eg.'x y z': ");
    scanf("%d %d %d", &num1, &num2, &num3);
    Point *p2 = new Point(num1, num2, num3);
    printf("Select the x,y,z coordinates for the third point eg.'x y z': ");
    scanf("%d %d %d", &num1, &num2, &num3);
    Point *p3 = new Point(num1, num2, num3);
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

  printf("\n\nStart:\n");
  d.printTriangle();

  Point translation = d.inputTranslateTriangle();
  d.translateTriangle(translation.x, 'x');
  d.translateTriangle(translation.y, 'y');
  d.translateTriangle(translation.z, 'z');

  printf("\nEnd:\n");
  d.printTriangle();
}