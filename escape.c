/* Ex. 3-2 $3.4 */
#include <stdio.h>

static void escape(char *s, const char *t);
static void epacse(char *s, const char *t);

int main(void)
{
  char buf[256], enc[256], dec[256];

  printf("Enter a sentence, try to hit special keys like alert(^G), "
         "backspace(^H), tab(^I), vertical tab(^K) and formfeed(^L):\n");
  fgets(buf, sizeof buf, stdin);
  escape(enc, buf);
  printf("\nEncoded:\n%s\n", enc);
  epacse(dec, enc);
  printf("\nRestored sentence:\n%s\n", dec);
  return 0;
}

/* escape: convert characters into escape sequences */
void escape(char *s, const char *t)
{
#define trans(a, b) case a: *s++ = '\\'; *s=b; break
  for (; (*s = *t++) != '\0'; s++)
    switch (*s) {
      trans('\a', 'a');         /* alert ^G */
      trans('\b', 'b');         /* backspace ^H */
      trans('\f', 'f');         /* formfeed ^L */
      trans('\n', 'n');
      trans('\r', 'r');
      trans('\t', 't');
      trans('\v', 'v');         /* vertical tab ^K */
      trans('\\', '\\');
      trans('\?', '\?');
      trans('\'', '\'');
      trans('\"', '\"');
    }
}

/* epacse: convert escape sequences back to actual characters */
void epacse(char *s, const char *t)
{
#define snart(a, b) case b: *s=a; break;
  for (; (*s = *t) != '\0'; s++, t++)
    if (*t == '\\')
      switch (*++t) {
        snart('\a', 'a');
        snart('\b', 'b');
        snart('\f', 'f');
        snart('\n', 'n');
        snart('\r', 'r');
        snart('\t', 't');
        snart('\v', 'v');
        snart('\\', '\\');
        snart('\?', '\?');
        snart('\'', '\'');
        snart('\"', '\"');
      default:
        --t;
      }
}
