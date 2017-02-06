// A collection of searching routines, assuming an arbitrary list.
// Each routine returns a sorted list.
// These routines were borrowed from the web and modified.

// The two relevant functions, selectionSort and mergeSort,
// take two arguments:
// Arg 1: The array to be sorted.
// Arg 2: The length of the array.

// mergeSort depends on a few auxilary functions, which we'll declare here:
void arraycopy(int source[], int sourceStartIndex, int target[], int targetStartIndex, int length);

void merge(int list1[], int list1Size, int list2[], int list2Size, int temp[]);

// Beyond that, here's the selection sort:
void selectionSort(int list[], int arraySize)
{
  for (int i = arraySize - 1; i >= 1; i--)
  {
    // Find the maximum in the list[0..i]
    double currentMax = list[0];
    int currentMaxIndex = 0;

    for (int j = 1; j <= i; j++)
    {
      if (currentMax < list[j])
      {
        currentMax = list[j];
        currentMaxIndex = j;
      }
    }

    // Swap list[i] with list[currentMaxIndex] if necessary;
    if (currentMaxIndex != i)
    {
      list[currentMaxIndex] = list[i];
      list[i] = currentMax;
    }
  }
}



// And here's the merge sort, which is a recursive algorithm!
void mergeSort(int list[], int arraySize)
{
  if (arraySize > 1)
  {
    // Merge sort the first half
    int *firstHalf = new int[arraySize / 2];
    arraycopy(list, 0, firstHalf, 0, arraySize / 2);
    mergeSort(firstHalf, arraySize / 2);

    // Merge sort the second half
    int secondHalfLength = arraySize - arraySize / 2;
    int *secondHalf = new int[secondHalfLength];
    arraycopy(list, arraySize / 2, secondHalf, 0, secondHalfLength);
    mergeSort(secondHalf, secondHalfLength);

    // Merge firstHalf with secondHalf
    int *temp = new int[arraySize];
    merge(firstHalf,  arraySize / 2, secondHalf, secondHalfLength, temp);
    arraycopy(temp, 0, list, 0, arraySize);
    delete [] temp;
    delete [] firstHalf;
    delete [] secondHalf;
  }
}

void merge(int list1[], int list1Size, int list2[], int list2Size, int temp[])
{
  int current1 = 0; // Index in list1
  int current2 = 0; // Index in list2
  int current3 = 0; // Index in temp

  while (current1 < list1Size && current2 < list2Size)
  {
    if (list1[current1] < list2[current2])
      temp[current3++] = list1[current1++];
    else
      temp[current3++] = list2[current2++];
  }

  while (current1 < list1Size)
    temp[current3++] = list1[current1++];

  while (current2 < list2Size)
    temp[current3++] = list2[current2++];
}

void arraycopy(int source[], int sourceStartIndex, int target[], int targetStartIndex, int length)
{
  for (int i = 0; i < length; i++)
  {
    target[i + targetStartIndex] = source[i + sourceStartIndex];
  }
}
