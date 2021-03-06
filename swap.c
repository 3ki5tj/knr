#include <stdio.h>

#define swap(type, x, y) { type z; z = (x), (x) = (y), (y) = z; }

int main(void)
{
  int i = 2, j = 5;
  double x = 3.14159, y = 2.71828;
  const char *s = "Hello", *t = "World";

  printf("before: %d, %d\n", i, j);
  swap(int, i, j);
  printf("after:  %d, %d\n", i, j);

  printf("before: %f, %f\n", x, y);
  swap(double, x, y);
  printf("after:  %f, %f\n", x, y);

  printf("before: %s, %s\n", s, t);
  swap(const char *, s, t);
  printf("after:  %s, %s\n", s, t);
  return 0;
}

