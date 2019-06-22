#include <constructible_from/constructible_from_tests.hpp>
#include <safe_types/safe_integer_tests.hpp>
#include <safe_types/safe_ptr_tests.hpp>
#include <safe_types/safe_ref_tests.hpp>
#include <type_traits/type_traits_tests.hpp>

#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

using namespace safe_types;
using namespace TypeTest;

using SafeIntPtr = TypeTest::Type;

template <class From>
using NonnarrowingConvertibleToInt = IsNonnarrowingConvertible<From, int*>;

using A = MakeUnique<
    class _A,
    ConstructibleFrom<int*, Signature<NonnarrowingConvertibleToInt>>::Type>;

using B = MakeUnique<
    class _B,
    ConstructibleFrom<int*, Signature<NonnarrowingConvertibleToInt>>::Type>;

int main() {
  auto ptr = new int{42};
  SafeIntPtr obj(ptr);
  obj = new int{43};
  obj = ptr;
  int* raw = obj;
  int*& ref = obj;
  std::cout << raw << std::endl;
  std::cout << *raw << std::endl;
  std::cout << ref << std::endl;

  {
    A a;
    B b;
    A c{new int{13}};
    c = new int{12};
    int* aptr = a;
    // a = b;  // compilation error as intended
    // A a2{b}; // compilation error as intended
    A a3{obj};
    // A a4 = B{}; // compilation error as intended
    // A a5{B{}}; // compilation error as intended
    int* ptr = b;
  }

  // SafeIntPtr p1 = 0; // compilation error as intended
  // SafeIntPtr p2(0); // compilation error as intended
  // SafeIntPtr p3{0}; // compilation error as intended
  SafeIntPtr p4{nullptr};
  SafeIntPtr p5 = nullptr;

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
