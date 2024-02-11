#include <stdio.h>
#include <string.h>

const char* msg = "Hello World";

#define HIST_CAP 256
size_t hist[HIST_CAP] = {0};

#define TABLE_CAP 64
char table[TABLE_CAP] = {0};

#define IDXES_CAP 64
size_t idxes[IDXES_CAP] = {0};

int main() {
  size_t msg_sz = strlen(msg);
  for (size_t i = 0; i < msg_sz; ++i) {
    hist[(size_t)msg[i]]++;
  }

  size_t table_sz = 0;
  for (size_t i = 0; i < HIST_CAP; ++i) {
    if (hist[i] > 0) {
      table[table_sz++] = (char)i;
    }
  }

  table[table_sz++] = '\0';
  printf("table: \"%s\"\n", table);

  size_t idxes_sz = 0;
  for (size_t i = 0; i < msg_sz; ++i) {
    for (size_t j = 0; j < TABLE_CAP; ++j) {
      if (msg[i] == table[j]) {
        idxes[idxes_sz++] = j;
      }
    }
  }

  printf("idxes: {");
  for (size_t i = 0; i < idxes_sz; ++i) {
    if (i > 0) printf(", ");
    printf("%ld", idxes[i]);
  }
  printf("}\n");

  printf("----------------------------------------\n");

  // https://stackoverflow.com/questions/14733761/printf-formatting-for-hexadecimal
  printf("table(hex): 0x");
  for (int i = strlen(table) - 1; i >= 0; --i) {
    printf("%02x", table[i]);
  }
  printf("\n");

  printf("idxes(hex): 0x");
  for (int i = idxes_sz - 1; i >= 0; --i) {
    printf("%01x", (char)idxes[i]);
  }
  printf("\n");

  return 0;
}
