#pragma once

#include "constructible_from.hpp"

using namespace constructible_from;
using namespace type_traits;

namespace TypeTest {

struct X {
  X(int*) {
  }
  X(int*, char*) {
  }
};

using DataType = int*;

template <class Rhs>
using MatchIntPtr = MatchAnyRef<int*, Rhs>;

template <class Rhs>
using MatchCharPtr = MatchAnyRef<char*, Rhs>;

template <class T>
using MatchNullptrT = MatchAnyRef<std::nullptr_t, T>;

template <class T>
using MatchIntPtrOrNull = Disjunction<MatchIntPtr<T>, MatchNullptrT<T>>;

template <class T>
using MatchCharPtrOrNull = Disjunction<MatchCharPtr<T>, MatchNullptrT<T>>;

using Type =
    ConstructibleFrom<DataType,
                      Signature<MatchIntPtr>,
                      Signature<MatchNullptrT>,
                      Signature<MatchIntPtrOrNull, MatchCharPtrOrNull>>::Type;

static_assert(std::is_constructible_v<Type, int*>,
              "Type should be constructible from int*.");
static_assert(std::is_constructible_v<Type, std::nullptr_t>,
              "Type should be constructible from std::nullptr_t.");
static_assert(std::is_constructible_v<Type, int*, std::nullptr_t>,
              "Type should be constructible from int* and std::nullptr_t.");
static_assert(std::is_constructible_v<Type, std::nullptr_t, char*>,
              "Type should be constructible from std::nullptr_t and char*.");
static_assert(
    std::is_constructible_v<Type, std::nullptr_t, std::nullptr_t>,
    "Type should be constructible from std::nullptr_t and std::nullptr_t.");

// TODO: fix problem with default constructors
// static_assert(!std::is_default_constructible_v<Type>,
//               "Type should not be default constructible.");

static_assert(!std::is_constructible_v<Type, std::nullptr_t, int*>,
              "Type should be constructible from std::nullptr_t and int*.");

static_assert(!std::is_constructible_v<Type, int>,
              "Type should not be constructible from int.");
static_assert(!std::is_constructible_v<Type, bool>,
              "Type should not be constructible from bool.");

static_assert(!std::is_constructible_v<Type, char*>,
              "Type should not be constructible from char*.");
static_assert(!std::is_constructible_v<Type, long long*>,
              "Type should not be constructible from long long*.");

}  // namespace TypeTest
