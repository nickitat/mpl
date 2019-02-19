#pragma once

#include "safe_integer.hpp"

#include <type_traits>

using namespace safe_types;

namespace SafeIntegerTests {

using SafeInt = safe_types::SafeInt<int>;

static_assert(std::is_constructible_v<SafeInt, int>, "");
static_assert(std::is_constructible_v<SafeInt, char>, "");
static_assert(!std::is_constructible_v<SafeInt, long long>, "");
static_assert(!std::is_constructible_v<SafeInt, unsigned int>, "");

}  // namespace SafeIntegerTests
