#include <safe_types/safe_integer.hpp>

#include <cassert>

void f() {
  // const int& i1 = SafeInt<int>(10121); // compilation error as intended
  SafeInt<int> a(10);
  int& i2 = a;
  std::cout << i2 << std::endl;
}