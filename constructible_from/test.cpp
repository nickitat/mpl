#include "tests.hpp"

#include <iostream>

int main() {
  using namespace TypeTest;
  auto ptr = new int{42};
  Type obj(ptr);
  std::cout << (int*)obj << std::endl;
  std::cout << *obj << std::endl;
  return 0;
}
