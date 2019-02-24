#pragma once

#include "safe_ref.hpp"

#include "../type_traits/type_traits.hpp"

#include <type_traits>

namespace SafeRefTests {

using SafeRef = safe_types::SafeRef<int>;

static_assert(std::is_constructible_v<SafeRef, int&>, "");
static_assert(!std::is_constructible_v<SafeRef, std::nullptr_t>, "");
static_assert(!std::is_constructible_v<SafeRef, char&>, "");
static_assert(!std::is_constructible_v<SafeRef, bool&>, "");
static_assert(!std::is_constructible_v<SafeRef, int>, "");
static_assert(!std::is_constructible_v<SafeRef, int&&>, "");
static_assert(!type_traits::IsConstructibleFromZeroV<SafeRef>, "");

}  // namespace SafeRefTests
