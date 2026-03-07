
#include "string.h"

void println0(const char * msg) {
  u64 n = 0;
  while (msg[n++]);
  println(msg, n);
}

void test_expression(u8 x, const char * msg) {
  if (!x) {
    println0(msg);
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
  println0("tests pass.");
  return 0;
}
