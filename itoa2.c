#include <stdio.h>

static void itoa(char *, int);
static void reverse(char *);

int main(void)
{
  int i = -123456;
  char buf[256]="Hello, World!";


  printf("before reverse: %s\n", buf);
  reverse(buf);
  printf("after reverse:  %s\n", buf);

  itoa(buf, i);
  printf("i=%d, itoa: %s\n", i, buf);
  return 0;
}

static void itoa(char *s, int n)
{
  if (n < 0) {
    n = -n;
    *s++ = '-';
    *s = '\0';
  }
  if (n / 10 > 0)
    itoa(s, n / 10);
  for (; *s; s++)
    ;
  *s++ = n % 10 + '0';
  *s = '\0';
}

static void reverse_low(char *s, char *t)
{
  char c;
  if (s >= t)
    return;
  c  = *s;
  *s = *t;
  *t = c;
  reverse_low(s + 1, t - 1);
}

void reverse(char *s)
{
  char *t;

  for (t = s; *t; t++)
    ;
  reverse_low(s, t - 1);
}

