#include "constructible_from.hpp"

namespace TypeTest {

struct X {
  X(int*) {
  }
  X(int*, std::nullptr_t) {
  }
};

using DataType = X;

template <class T>
using MatchIntPtr = std::is_same<int*, T>;

template <class T>
using MatchNullptrT = std::is_same<std::nullptr_t, T>;

using Type = ConstructibleFrom<DataType,
                               Domains<MatchIntPtr>,
                               Domains<MatchNullptrT>,
                               Domains<MatchIntPtr, MatchNullptrT>>::Type;

static_assert(std::is_constructible_v<Type, int*>,
              "TypeTest should be constructible from int*.");
static_assert(std::is_constructible_v<Type, std::nullptr_t>,
              "TypeTest should be constructible from std::nullptr_t.");
static_assert(std::is_constructible_v<Type, int*, std::nullptr_t>,
              "TypeTest should be constructible from std::nullptr_t.");

// TODO: fix problem with default constructors
// static_assert(!std::is_default_constructible_v<Type>,
//               "Type should not be default constructible.");

static_assert(!std::is_constructible_v<Type, int>,
              "TypeTest should not be constructible from int.");
static_assert(!std::is_constructible_v<Type, bool>,
              "TypeTest should not be constructible from bool.");

static_assert(!std::is_constructible_v<Type, char*>,
              "TypeTest should not be constructible from char*.");
static_assert(!std::is_constructible_v<Type, long long*>,
              "TypeTest should not be constructible from long long*.");

static_assert(sizeof(Type) == sizeof(DataType));

}  // namespace TypeTest
