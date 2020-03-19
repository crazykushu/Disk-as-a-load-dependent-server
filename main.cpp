#include <iostream>
#include <stdio.h>
#include <random>
#include <math.h>

using namespace std;

#define xmax 8057
#define divider 1686
#define t 1.5455
#define c 0.3197
#define r 0.3868


int * array_constructor(int * &intPtr, int &size, int a, int b )
{
   if (size <= 0)
   {
      intPtr = nullptr;
      return intPtr;
   }
   else
   {
      default_random_engine generator; 
      uniform_int_distribution<int> distribution(a, b);
      intPtr = new int [size];
	      for(int i = 0; i < size; i++)
	      {
		      intPtr[i] = distribution(generator) ; //uniform distribution of a random number
	      }
      distribution.reset();  
	    return intPtr;
   }
}

double seekTime(int position)
{
  double result;
  if (position < divider)
  {
    result = t + c * pow((position - 1), r);
  }
  else
  {
    result = (c * r *(position - divider)) / pow((divider - 1), (1 - r)) + t + c * pow((divider - 1), r);
  }

  return result;
}

int findNext(int *&intPtr, int currentPosition, int size)
{
  int minimum = 9000, index, difference;
  for (int i = 0; i < size;i++)
  {
    difference = abs(currentPosition - intPtr[i]);
    if (minimum > difference)
    {
      minimum = difference;
      index = i;
    }
  }
  return index;
}

int main() {
  int * intPtr = nullptr; //array pointer
  int currentIndex;

  int mincyl = 1;
	for (int size = 1; size < 21; size++)
  {
    double totalTime = 0.000;
    array_constructor(intPtr, size, mincyl, xmax);
    int x = (rand() % (xmax - mincyl + 1)) + mincyl; //random initial position
    cout << x << endl;
    for (int i = 0; i < 10000; i++)
    {
      currentIndex = findNext(intPtr, x, size);
      totalTime = totalTime + seekTime(intPtr[currentIndex]);
      x = intPtr[currentIndex];
      intPtr[currentIndex] = (rand() % (xmax - mincyl + 1)) + mincyl;
    }
    cout << "Average access time is " << totalTime / 10000 << "ms for a Q value of: " << size << endl;
  }
}