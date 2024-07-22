#include <iostream>

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
    // prints everything in the array in one line seperated by a space
    std::cout << array[i] << " ";
  // new line /n
  std::cout << std::endl;
}

void deleteArray(int *array)
{
  delete[] array;
}

int main()
{
  int arraySize;
  std::cin >> arraySize;
  int *arr = createArray(arraySize);
  initializeArray(arr, arraySize);
  printArray(arr, arraySize);
  deleteArray(arr);
}
