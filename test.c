
#include "string.h"

static u64 tests_failed = 0;

void println0(const char * msg) {
  u64 n = 0;
  while (msg[n++]);
  println(msg, n);
}

void test_expression(u8 x, const char * msg) {
  if (!x) {
    println0(msg);
    tests_failed++;
  }
}

void test_memset() {
  const u64 n = 10;
  char set = 'A';
  char m[n];

  char * x = (char *)memset(m, set, n);

  for (u64 i = 0; i < n; i++) {
    test_expression(m[i] == set, "test_memset failed.");
  }
  test_expression(x == m, "test_memset return failed.");
}

void test_memcpy() {
  const u64 n = 10;
  char set = '1';
  char m[n], e[n];

  memset(e, set, n);

  char * x = (char *)memcpy(m, e, n);

  for (u64 i = 0; i < n; i++) {
    test_expression(m[i] == e[i], "test_memcpy failed.");
  }
  test_expression(x == m, "test_memcpy return failed.");
}

void test_memmove() {
  // non overlapping
  const u64 n = 10;
  char set = '1';
  char m[n], e[n];

  memset(e, set, n);

  char * x = (char *)memmove(m, e, n);

  for (u64 i = 0; i < n; i++) {
    test_expression(m[i] == e[i], "test_memmove failed.");
  }
  test_expression(x == m, "test_memmove return failed.");

  // 1 byte overlapping
  char a[2 * n - 1];
  memset(a, '2', n);

  x = memmove(&a[n - 1], a, n);

  char * b = &a[n - 1];
  for (u64 i = 0; i < n; i++) {
    test_expression(b[i] == a[i], "test_memmove (overlapping) failed.");
  }
  test_expression(x == m, "test_memmove (overlapping) return failed.");
}

int main() {
  test_memset();
  test_memcpy();
  test_memmove();

  if (tests_failed == 0) {
    println0("tests pass.");
    return 0;
  }

  return tests_failed;
}
