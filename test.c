
#include "string.h"

void test_expression(u8 x, const char * msg) {
  u64 n = 0;
  while (msg[n++]);

  if (!x) {
    println(msg, n);
    exit(-1);
  }
}

void test_memset() {
  const u64 n = 10;
  char set = 'A';
  char m[n];

  memset(m, set, n);

  for (u64 i = 0; i < n; i++) {
    test_expression(m[i] == set, "test_memset failed.");
  }
}

int main() {
  test_memset();
  return 0;
}
