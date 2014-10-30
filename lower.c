/* Ex. 2-10 $ 2.11 */
#include <stdio.h>
#include <ctype.h>

static int lower(int c)
{
  return (c >= 'A' && c <= 'Z' && isalpha(c)) ? c - 'A' + 'a' : c;
}

int main(void)
{
  char s[32]="{Hello, World}", t[32], *p, *q;

  for (p = s, q = t; (*q++ = (char) lower(*p++)) != '\0';)
    ;
  printf("Before: %s. After: %s.\n", s, t);
  return 0;
}

