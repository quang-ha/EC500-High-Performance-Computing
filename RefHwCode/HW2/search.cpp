/* RCB and ESW, 2016-02-05, Comparing different search algorithms.
   Various codes are borrowed from the web.
   Updated 2017-01-30. */

#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>

#include "search.h"
#include "sort.h"

using std::cout; 
using std::endl;

// A function to print arrays.
void printArray(int list[], int arraySize)
{
  cout << " --------" << endl;
  for (int i = 0; i < arraySize; i++)
  {
    cout << list[i] <<  " " << endl;
  }
  cout << " --------" << endl;
}


int main()
{
  // Feel free to change this!
  const int Nsize =  10000000; // 10^7
  int * list = new  int[Nsize];

  // Iterators.
  int i;

  // Counters 
  int BinCount; // counter for binary search. 
  int LinCount; // counter for linear search. 
  int DctCount; // counter for dictionary search.

  /*
  time_t time(time_t *time);
  This returns the current calendar time of the system 
  in number of seconds elapsed  since January 1, 1970. 
  If the system has no time, .1 is returned.
  */
  int time_seconds = time(0);
  srand(time_seconds%100); // seed the random number generator.

  // Fill the array with random numbers.
  for(i = 0; i < Nsize; i++)
  {
    list[i] =  rand()%Nsize;
  }

  // Randomly choose an element to search for.
  int find = list[rand()%Nsize] ;

  // First, search with a linear search. A linear search doesn't depend
  // on a list being sorted.
  cout << "Searching for key = "<< find << endl;
  i = linearSearch(list,find ,Nsize, LinCount);

  // Print the number of iterations compared to the average.
  cout <<" Linear search found at  "<< i << 
  " with " <<LinCount << " iterations  compared to Nsize/2 " << Nsize/2 << endl;

  // If the array is small enough, print it out... if you are so interested.
  /*
  if(Nsize < 1000)
  {
    cout << "Random List of Numbers  " << endl;
    printArray(list, Nsize);  
  }
  */

  // Next, let's look at a binary search and a dictionary search.
  // This requires a sorted list. Feel free to play with these if
  // you want. 
  // WARNING: the selection sort takes a long time if Nsize gets
  // into the millions... you probably have better things to do.
  
  //selectionSort(list, Nsize);
  mergeSort(list, Nsize);  

  // If the array is small enough, print it out... if you are so interested.
  /*
  if(Nsize < 1000)
  {
    cout << "Sorted List of  Numbers  " << endl;
    printArray(list, Nsize); 
  }
  */

  //Perform a binary search. 
  i = binarySearch(list,find ,Nsize, BinCount); 

  // Print the number of iterations compared to the average.
  cout <<" Binary  search found at  "<< i <<
  " with " <<BinCount << " iterations  compared to log2(Nsize) " << log(Nsize)/log(2) << endl;

  // Perform a dictionary search. 
  i = dictionarySearch(list,find ,Nsize, DctCount);  

  // Print the number of iterations compared to the average.
  cout <<" Dictionary   found at  "<< i << 
  " with " <<DctCount << " iterations compared to log2(log2(Nsize)  " << log(log(Nsize)/log(2))/log(2) <<  endl; 

  // Free the allocated memory.
  delete [] list;

  return 0;
}



