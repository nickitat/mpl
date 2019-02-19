#pragma once

#include "type_traits.hpp"

using namespace type_traits;

namespace TypeTraitsTests {

static_assert(IsNonnarrowingConvertibleV<int, int>, "");
static_assert(!IsNonnarrowingConvertibleV<int, char>, "");
static_assert(IsNonnarrowingConvertibleV<int, long long>, "");
static_assert(!IsNonnarrowingConvertibleV<int, unsigned int>, "");

}  // namespace TypeTraitsTests
