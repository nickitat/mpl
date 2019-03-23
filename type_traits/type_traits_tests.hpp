#pragma once

#include <type_traits/type_traits.hpp>

using namespace type_traits;

namespace TypeTraitsTests {

static_assert(IsNonnarrowingConvertibleV<int, int>, "");
static_assert(!IsNonnarrowingConvertibleV<int, char>, "");
static_assert(IsNonnarrowingConvertibleV<int, long long>, "");
static_assert(!IsNonnarrowingConvertibleV<int, unsigned int>, "");

static_assert(IsConstructibleFromZeroV<int>, "");
static_assert(IsConstructibleFromZeroV<unsigned char>, "");
static_assert(IsConstructibleFromZeroV<short>, "");
static_assert(IsConstructibleFromZeroV<bool>, "");
static_assert(IsConstructibleFromZeroV<int*>, "");
static_assert(IsConstructibleFromZeroV<char*>, "");
static_assert(IsConstructibleFromZeroV<unsigned short*>, "");
static_assert(IsConstructibleFromZeroV<char&&>, "");
static_assert(!IsConstructibleFromZeroV<int&>, "");
static_assert(!IsConstructibleFromZeroV<void>, "");

}  // namespace TypeTraitsTests
