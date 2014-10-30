#include <stdio.h>

static void reverse_low(char *s, char *t)
{
  char c;

  if (s >= t) return;
  c = *s, *s = *t, *t =  c;
  reverse_low(s + 1, t - 1);
}

static void reverse(char *s)
{
  char *t;

  for (t = s; *t; t++) ;
  reverse_low(s, t - 1);
}

int main(void)
{
  char buf[256] = "Hello, World!";

  printf("before reverse: %s\n", buf);
  reverse(buf);
  printf("after reverse:  %s\n", buf);
  return 0;
}

