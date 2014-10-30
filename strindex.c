/* Ex. 4.1 $4.1; Ex. 5-6 $5.5 */
#include <stdio.h>

/* strindex: return index of t in s, -1 if none */
static int strindex(const char *s, const char *t)
{
  const char *r, *p, *q;

  for (r = s; *r; r++) {
    for (p = r, q = t; *q && *p == *q; p++, q++)
      ;
    if (q > t && *q == '\0')
      return r - s;
  }
  return -1;
}

/* strindex: return index of t in s from right, -1 if none */
static int strrindex(const char *s, const char *t)
{
  const char *r, *p, *q, *sz, *tz;

  for (sz = s; *sz; sz++)
    ;
  --sz;
  for (tz = t; *tz; tz++)
    ;
  --tz;
  for (r = sz; r >= s; r--) {
    for (p = r, q = tz; q >= t && *p == *q; p--, q--)
      ;
    if (q < tz && q < t)
      return p - s + 1;
  }
  return -1;
}

int main(int argc, char *argv[])
{
  const char *s = "Hello, hello!", *t = "lo";
  int i, ir;

  if (argc >= 3) s = argv[1], t = argv[2];
  i = strindex(s, t);
  ir = strrindex(s, t);
  printf("index strindex(\"%s\", \"%s\")=%d strrindex(\"%s\", \"%s\")=%d\n",
      s, t, i, s, t, ir);

  return 0;
}

