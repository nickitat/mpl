#include "constructible_from.hpp"

namespace SafeIntTest {

template <class T>
using MatchIntPtr = std::is_same<int*, T>;

using PtrWrapper = ConstructibleFrom<int*, MatchIntPtr>::Type;

static_assert(std::is_constructible_v<PtrWrapper, int*>,
              "SafeInt should be constructible from int.");
static_assert(!std::is_constructible_v<PtrWrapper, char*>,
              "SafeInt should be constructible from int.");
static_assert(!std::is_constructible_v<PtrWrapper, long long*>,
              "SafeInt should be constructible from int.");
static_assert(!std::is_constructible_v<PtrWrapper, int>,
              "SafeInt should be constructible from int.");

static_assert(sizeof(PtrWrapper) == sizeof(int*));

}  // namespace SafeIntTest
