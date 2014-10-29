/* Ex. 5-3, 5-4, 5-5, 5-6 $5.5 */
#include <stdio.h>

static void strcat(char *s, const char *t);   /* Ex. 5-3 */
static int  strend(char *s, const char *t);   /* Ex. 5-4 */
static char *strncpy(char *s, const char *t, size_t n);  /* Ex. 5-5 */
static char *strncat(char *s, const char *t, size_t n);
static char *strncmp(const char *s, const char *t, size_t n);
static char *reverse(char *s);  /* Ex. 5-6 */

int main(void)
{
  char s[SIZE]="Hello, ", t[SIZE]="world";

  strcat(s, t);
  printf("after strcat %s\n", s, t);
  return 0;
}

