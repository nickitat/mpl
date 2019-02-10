#include "constructible_from.hpp"

#include <iostream>
using namespace std;

struct A {};
struct B {};
struct C {};

template <class... Ts>
struct D : Ts... {
  using Ts::Ts...;
};

int main() {
  using Type = ConstructibleFrom<int*, int*>::Type;

  int* arg = new int{42};
  Type d(arg);
  auto data = reinterpret_cast<int**>(&d.mem);
  cout << arg << endl;
  cout << data << endl;
  cout << *data << endl;
  cout << **data << endl;

  cout << d << endl;
  cout << *d << endl;

  return 0;
}
