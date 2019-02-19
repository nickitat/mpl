#include "constructible_from/constructible_from_tests.hpp"

#include "safe_types/safe_integer_tests.hpp"
#include "type_traits/type_traits_tests.hpp"

#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

int main() {
  using namespace TypeTest;
  auto ptr = new int{42};
  Type obj(ptr);
  std::cout << (int*)obj << std::endl;
  std::cout << *obj << std::endl;
  return 0;
}
