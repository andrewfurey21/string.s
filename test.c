
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
  const u64 n = 20;
  const u8 set = 'b';
  u8 a[n], b[n];
  memset(a, set, n);
  memset(b, set, n);

  i32 equal = memcmp(a, b, n);
  test_expression(equal == 0, "test_memcmp failed, not equal.");

  a[10] = 'd';
  i32 greater = memcmp(a, b, n);
  test_expression(greater == 1, "test_memcmp failed, not greater.");

  a[10] = set;
  a[15] = 'a';
  i32 less = memcmp(a, b, n);
  test_expression(less == -1, "test_memcmp failed, not less.");
}

void test_memchr() {
  const u64 n = 10;
  u8 a[n];
  memset(a, 0, n);
  const u8 find = 'a';
  const u8 cant_find = 'd';
  a[n - 2] = find;

  // found
  u8 * result = (u8 *)memchr(a, find, n);
  test_expression(*result == find, "test_memchr failed, wrong found.");

  // not found
  result = (u8 *)memchr(a, cant_find, n);
  test_expression(result == NULL, "test_memchr failed, wrong not found.");
}

void test_memccpy() {
  const u64 n = 10;
  u8 a[n], b[n];

  int until = 'd';
  const u8 seta = 'a';
  const u8 setb = 'b';
  void * result;

  // copy all
  memset(a, seta, n);
  memset(b, setb, n);
  result = memccpy(b, a, until, n);
  test_expression(memcmp(a, b, n) == 0, "test_memccpy failed, wrong copy all.");
  test_expression(result == b + n, "test_memccpy failed, wrong copy all return.");

  // copy first
  memset(b, setb, n);
  a[0] = until;
  result = memccpy(b, a, until, n);
  test_expression(b[0] == until, "test_memccpy failed, wrong copy first.");
  test_expression(result == b + 1, "test_memccpy failed, wrong copy first return.");

  // copy until
  memset(a, seta, n);
  memset(b, setb, n);
  const u64 m = n - 5;
  a[m - 1] = until;
  result = memccpy(b, a, until, n);
  test_expression(memcmp(b, a, m) == 0, "test_memccpy failed, wrong copy until.");
  test_expression(b[m - 1] == until, "test_memccpy failed, wrong copy until end.");
  test_expression(result == b + m, "test_memccpy failed, wrong copy until return.");

  // copy none
  memset(a, seta, n);
  memset(b, setb, n);
  result = memccpy(b, a, until, 0);
  test_expression(result == b, "test_memccpy failed, wrong copy none return.");
}

int main() {
  test_memset();
  test_memcpy();
  test_memmove();
  test_memcmp();
  test_memchr();
  test_memccpy();

  if (tests_failed == 0) {
    println0("tests pass.");
    return 0;
  }

  return tests_failed;
}
