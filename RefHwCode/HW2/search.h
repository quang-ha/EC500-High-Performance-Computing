// A collection of searching routines, assuming a sorted list.
// Each routine returns 'i' such that list[i] == key. 
// These routines were borrowed from the web and modified. 

// Each routine takes four arguments:
// Arg 1: the array of integers 'list'
// Arg 2: the value to search for 'key'
// Arg 3: the length of the array (C doesn't know about the size of its arrays)
// Arg 4: a reference to a counter which is updated with the number of steps. 

int binarySearch(int list[], int key, int arraySize, int& count)
{
  int low = 0;
  int high = arraySize - 1;
  count = 0;
  while (high >= low)
  {
    count++;
    int mid = (low + high) / 2;
    if (key < list[mid])
      high = mid - 1;
    else if (key == list[mid])
      return mid;
    else
      low = mid + 1;
  }

  return -1;
}


int dictionarySearch(int list[], int key, int arraySize, int& count)
{
  int low = 0;
  int high = arraySize - 1;
  double x;

  count = 0;
  while (high >= low)
  {
    count++;
    x = (key - list[low])/(double) (list[high] - list[low] ) ;

    int  mid = x * (high - low) + low;
    if (key < list[mid])
      high = mid - 1;
    else if (key == list[mid])
      return mid;
    else
      low = mid + 1;
    }

    return -1;
}


int linearSearch(int list[], int key, int arraySize, int& count)
{
  count = 0;
  for (int i = 0; i < arraySize; i++)
  {
    count++;
    if (key == list[i])
      return i;
  }

  return -1;
}
