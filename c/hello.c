#include <stdio.h>
#include <stdint.h>

int main(void) {
  uint64_t ies = 0x357620655410;
  while (ies) putchar((0x726f6c6564574820 >> (((ies >>= 4) & 0xf) << 3)));
  putchar('\n');
  return 0;
}
