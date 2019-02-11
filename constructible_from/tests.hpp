#include "constructible_from.hpp"

namespace PtrWrapperTest {

template <class T>
using MatchIntPtr = std::is_same<int*, T>;

template <class T>
using MatchNullptrT = std::is_same<std::nullptr_t, T>;

template <class T>
using PtrWrapperPred = std::disjunction<MatchIntPtr<T>, MatchNullptrT<T>>;

using PtrWrapper = ConstructibleFrom<int*, Domain<PtrWrapperPred>>::Type;

static_assert(std::is_constructible_v<PtrWrapper, int*>,
              "PtrWrapperTest should be constructible from int*.");
static_assert(std::is_constructible_v<PtrWrapper, std::nullptr_t>,
              "PtrWrapperTest should be constructible from std::nullptr_t.");

static_assert(!std::is_default_constructible_v<PtrWrapper>,
              "PtrWrapper should not be default constructible.");
static_assert(!std::is_constructible_v<PtrWrapper, int>,
              "PtrWrapperTest should not be constructible from int.");
static_assert(!std::is_constructible_v<PtrWrapper, bool>,
              "PtrWrapperTest should not be constructible from bool.");

static_assert(!std::is_constructible_v<PtrWrapper, char*>,
              "PtrWrapperTest should not be constructible from char*.");
static_assert(!std::is_constructible_v<PtrWrapper, long long*>,
              "PtrWrapperTest should not be constructible from long long*.");

static_assert(sizeof(PtrWrapper) == sizeof(int*));

}  // namespace PtrWrapperTest

// namespace experimental {

// template <class T>
// using MatchIntPtr = std::is_same<int*, T>;

// template <class T>
// using MatchChar = std::is_same<char, T>;

// using CFIntPtr = Domain<MatchIntPtr>;
// using CFChar = Domain<MatchChar>;

// using Union = ConstructibleFrom<void, CFIntPtr>;

// }  // namespace experimental
