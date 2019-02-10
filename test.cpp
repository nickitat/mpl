#include "constructible_from/constructible_from_tests.hpp"
#include "safe_types/safe_integer_tests.hpp"
#include "safe_types/safe_ptr_tests.hpp"
#include "safe_types/safe_ref_tests.hpp"
#include "type_traits/type_traits_tests.hpp"

#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

using namespace safe_types;

using SafeIntPtr = TypeTest::Type;

int main() {
  auto ptr = new int{42};
  SafeIntPtr obj(ptr);
  obj = new int{43};
  int* raw = static_cast<int*>(obj);
  int*& ref = static_cast<int*&>(obj);
  std::cout << raw << std::endl;
  std::cout << *raw << std::endl;
  std::cout << ref << std::endl;

  // const int& i1 = SafeInt<int>(10121); // compilation error as intended
  SafeInt<int> a(10);
  int& i2 = a;
  std::cout << i2 << std::endl;

  int aa = 113;
  int& ra = aa;
  SafeRef<int> sr1(aa);
  SafeRef<int> sr2(ra);
  // SafeRef<int> sr3(11); // compilation error as intended
  return 0;
}
