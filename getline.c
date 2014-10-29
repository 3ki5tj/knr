/* Ex. 2-2 $2.6 */
#include <stdio.h>

/* getline_if: get a line s of maximal lim-1 characters without using :? */
static int getline_if(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim - 1; i++)
    if ((c = getchar()) == EOF)
      break;
    else if (c == '\n')
      break;
    else
      s[i] = c;
  if (c=='\n')
    s[i++]='\n';
  s[i]='\0';
  return i;
}

int main(void)
{
  char buf[128];
  int i;

  i = getline_if(buf, sizeof buf);
  printf("\nYou entered %d characters: %s", i, buf);
  return 0;
}

