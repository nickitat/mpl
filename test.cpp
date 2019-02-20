#include "constructible_from/constructible_from_tests.hpp"
#include "safe_types/safe_integer_tests.hpp"
#include "type_traits/type_traits_tests.hpp"

#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

using SafeIntPtr = TypeTest::Type;

int main() {
  auto ptr = new int{42};
  SafeIntPtr obj(ptr);
  int* raw = static_cast<int*>(obj);
  int*& ref = static_cast<int*&>(obj);
  std::cout << raw << std::endl;
  std::cout << *raw << std::endl;
  std::cout << ref << std::endl;
  return 0;
}
 