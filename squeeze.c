/* Ex. 2-4 $2.8 */
#include <stdio.h>
#include <string.h>

static void squeeze(char *s, const char *t);
static void squeeze2(char *s, const char *t);

#define SIZE 256
int main(int argc, char *argv[])
{
  char buf[SIZE], buf2[SIZE], *s="Hello", *t="World";

  if (argc >= 3) s = argv[1], t = argv[2];
  strcpy(buf2, strncpy(buf, s, SIZE-1));
  squeeze(buf, t);
  squeeze2(buf2, t);
  printf("squeeze(%s,%s) = %s (version 1) %s (version 2)\n", s, t, buf, buf2);
  return 0;
}

#include <limits.h>

/* squeeze: remove characters in t from string s */
void squeeze(char *s, const char *t)
{
  char *p;
  const char *q;

  for (p = s; *s; s++) {
    for (q = t; *q && *q != *s; q++)
      ;
    if (*q == '\0')
      *p++ = *s;
  }
  *p = '\0';
}

/* squeez2: same as squeeze,, */
void squeeze2(char *s, const char *t)
{
  int has[1<<CHAR_BIT] = {0};
  char *p;

  for (; *t; t++)
    has[*t - CHAR_MIN] = 1;
  for (p = s; *s; s++)
    if (!has[*s - CHAR_MIN])
      *p++ = *s;
  *p = '\0';
}


