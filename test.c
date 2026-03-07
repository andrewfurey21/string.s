
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
  u8 set = 'A';
  u8 m[n];

  u8 * x = (u8 *)memset(m, set, n);

  for (u64 i = 0; i < n; i++) {
    test_expression(m[i] == set, "test_memset failed.");
  }
  test_expression(x == m, "test_memset return failed.");
}

void test_memcpy() {
  const u64 n = 10;
  u8 set = '1';
  u8 m[n], e[n];

  memset(e, set, n);

  u8 * x = (u8 *)memcpy(m, e, n);

  for (u64 i = 0; i < n; i++) {
    test_expression(m[i] == e[i], "test_memcpy failed.");
  }
  test_expression(x == m, "test_memcpy return failed.");
}

void test_memmove() {
  // non overlapping
  const u64 n = 10;
  u8 set = '1';
  u8 m[n], e[n];

  memset(e, set, n);

  u8 * x = (u8 *)memmove(m, e, n);

  for (u64 i = 0; i < n; i++) {
    test_expression(m[i] == e[i], "test_memmove failed.");
  }
  test_expression(x == m, "test_memmove return failed.");

  // 1 byte overlapping
  u8 a[2 * n - 1];
  memset(a, '2', n);

  x = memmove(&a[n - 1], a, n);

  u8 * b = &a[n - 1];
  for (u64 i = 0; i < n; i++) {
    test_expression(b[i] == a[i], "test_memmove (overlapping) failed.");
  }
  test_expression(x == b, "test_memmove (overlapping) return failed.");
}

void test_memcmp() {
  const u64 n = 3;
  const u8 set = 'b';
  u8 a[n], b[n];
  memset(a, set, n);
  memset(b, set, n);

  i32 equal = memcmp(a, b, n);
  test_expression(equal == 0, "test_memcmp failed, not equal.");

  a[1] = 'd';
  i32 greater = memcmp(a, b, n);
  test_expression(greater == 1, "test_memcmp failed, not greater.");

  a[1] = set;
  a[2] = 'a';
  i32 less = memcmp(a, b, n);
  test_expression(less == -1, "test_memcmp failed, not less.");
}

int main() {
  test_memset();
  test_memcpy();
  test_memmove();
  test_memcmp();

  if (tests_failed == 0) {
    println0("tests pass.");
    return 0;
  }

  return tests_failed;
}
