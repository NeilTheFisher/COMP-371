#include <iostream>

int main()
{
  int *arr = createArray(10);
  initializeArray(arr, 10);
  printArray(arr, 10);
  deleteArray(arr);
}

int *createArray(int size)
{
  return new int[size];
}

void initializeArray(int *array, int size)
{
  for (int i = 0; i < size; i++)
  {
    array[i] = i;
  }
}

void printArray(int *array, int size)
{
  for (int i = 0; i < size; i++)
    std::cout << array[i] << " ";
  std::cout << std::endl;
}

void deleteArray(int *array)
{
  delete[] array;
}