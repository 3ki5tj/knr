/* Ex. 2-6, 2-7, 2-8 and 2-9  $$2.8 and 2.9 */
#include <stdio.h>

static unsigned setbits(unsigned, int, int, unsigned);  /* Ex. 2-6 */
static unsigned invert(unsigned, int, int);     /* Ex. 2-7 */
static unsigned rightrot(unsigned, int);        /* Ex. 2-8 */
static int bitcount(unsigned);  /* Ex. 2-9 */

int main(int argc, char *argv[])
{
  unsigned x = 0x12345, y = 0x17;
  int p = 11, n = 8;

  printf("setbits(%#x, %d, %d, %#x) = %#x\n", x, p, n, y, setbits(x, p, n, y));

  printf("invert(%#x, %d, %d) = %#x\n", x, p, n, invert(x, p, n));

  printf("rightrot(%#x, %d) = %#x\n", x, n, rightrot(x, n));

  x = 0x21040F0;
  printf("bitcount(%#x) = %d\n", x, bitcount(x));
  return 0;
}

/* setbits: return x with the n bits that begin at position p set to the rightmost n bits of y */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  return (x & ~(~(~0u << n) << (p + 1 - n))) | (y & ~(~0u << n)) << (p + 1 - n);
}

/* invert: returns x with the n bits that begin at position p inverted */
unsigned invert(unsigned x, int p, int n)
{
  return x ^ ~(~0u << n) << (p + 1 - n);
}

/* rightrot: return x rotated to the right by n bits */
unsigned rightrot(unsigned x, int n)
{
  /* for 32-bit *//* return (~(~0<<n)&x) << (32-n) | x>>n; */
  while (n-- > 0)
    x = (x & 1 ? ~(~0u >> 1) : 0) | (x >> 1);
  return x;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
  int i;
  for (i = 0; x; i++)
    x &= x - 1;
  return i;
}
