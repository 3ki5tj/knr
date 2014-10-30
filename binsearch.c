/* Ex. 3-1 $3.3 */
#include <stdio.h>
#include <stdlib.h>

/* binsearch: find x in an array sorted in ascending order */
static int binsearch(int x, int v[], int n)
{
  int low, high, mid;

  for (low = 0, high = n; low < high;)
    if (x < v[mid = (low + high) / 2])
      high = mid;
    else
      low = mid + 1;
  return (--low >= 0 && v[low] == x) ? low : -1;
}

int main(int argc, char *argv[])
{
  int x = 21, arr[10] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

  if (argc == 2) x = atoi(argv[1]);
  printf("x %d, index %d\n", x, binsearch(x, arr, 10));
  return 0;
}

