#pragma once

#include "constructible_from.hpp"

using namespace constructible_from;

namespace TypeTest {

struct X {
  X(int*) {
  }
  X(int*, std::nullptr_t) {
  }
};

using DataType = int*;

template <class Rhs>
using MatchIntPtr = std::is_same<int*, Rhs>;

template <class T>
using MatchNullptrT = std::is_same<std::nullptr_t, T>;

using Type = ConstructibleFrom<DataType,
                               Domains<MatchIntPtr>,
                               Domains<MatchNullptrT>,
                               Domains<MatchIntPtr, MatchNullptrT>>::Type;

static_assert(std::is_constructible_v<Type, int*>,
              "Type should be constructible from int*.");
static_assert(std::is_constructible_v<Type, std::nullptr_t>,
              "Type should be constructible from std::nullptr_t.");
static_assert(std::is_constructible_v<Type, int*, std::nullptr_t>,
              "Type should be constructible from int* and std::nullptr_t.");

// TODO: fix problem with default constructors
// static_assert(!std::is_default_constructible_v<Type>,
//               "Type should not be default constructible.");

static_assert(!std::is_constructible_v<Type, int>,
              "Type should not be constructible from int.");
static_assert(!std::is_constructible_v<Type, bool>,
              "Type should not be constructible from bool.");

static_assert(!std::is_constructible_v<Type, char*>,
              "Type should not be constructible from char*.");
static_assert(!std::is_constructible_v<Type, long long*>,
              "Type should not be constructible from long long*.");

}  // namespace TypeTest
