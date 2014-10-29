/* Ex. 2-5 $2.8 */
#include <stdio.h>
#include <string.h>
#include <limits.h>

static int any(const char *, const char *);
static int any2(const char *, const char *);

#define BUFSIZE 256
int main(int argc, char *argv[])
{
  char *s1 = "Hello", *s2 = "World", *p;
  int ret, ret2, ref;

  if (argc == 3)
    s1 = argv[1], s2 = argv[2];

  ret = any(s1, s2);
  ret2 = any2(s1, s2);
  ref = (p = strpbrk(s1, s2)) ? p - s1 : -1;

  printf("any(%s,%s) = %d (ver 1) %d (ver 2)  ||  %d c.f. strpbrk()\n",
         s1, s2, ret, ret2, ref);

  return 0;
}

/* any: find the first occurence in s of any character in t */
int any(const char *s, const char *t)
{
  int i, k;
  for (i = 0; s[i]; i++)
    for (k = 0; t[k]; k++)
      if (t[k] == s[i])
        return i;
  return -1;
}

/* any2: a look-up table version of any */
int any2(const char *s, const char *t)
{
  int has[1 << CHAR_BIT] = { 0 };
  for (; *t; t++)
    has[*t - CHAR_MIN] = 1;
  for (t = s; *t; t++)
    if (has[*t - CHAR_MIN])
      return t - s;
  return -1;
}
