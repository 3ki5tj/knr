/* Ex. 2-10 $ 2.11 */
#include <stdio.h>
#include <ctype.h>

static int lower(int ch)
{
  return (ch>='A' && ch<='Z' && isalpha(ch)) ? ch-'A'+'a' : ch;
}

int main(void)
{
  char s[32]="{Hello, World}", t[32], *p, *q;

  for (p = s, q = t; (*q++=lower(*p++)) != '\0';)
    ;
  printf("Before: %s. After: %s.\n", s, t);
  return 0;
}

