#pragma once

#include "type_traits.hpp"

namespace TypeTraitsTests {

static_assert(IsNonnarrowingConvertible<int, int>, "");
static_assert(!IsNonnarrowingConvertible<int, char>, "");
static_assert(IsNonnarrowingConvertible<int, long long>, "");

static_assert(!IsNonnarrowingConvertible<int, unsigned int>, "");

}