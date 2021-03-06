#pragma once

#include <safe_types/safe_ptr.hpp>

#include <type_traits/type_traits.hpp>

#include <type_traits>

namespace SafePtrTests {

using SafePtr = safe_types::SafePtr<int>;

static_assert(std::is_constructible_v<SafePtr, int*>, "");
static_assert(std::is_constructible_v<SafePtr, std::nullptr_t>, "");
static_assert(!std::is_constructible_v<SafePtr, char*>, "");
static_assert(!std::is_constructible_v<SafePtr, bool>, "");
static_assert(!std::is_constructible_v<SafePtr, int>, "");
static_assert(!type_traits::IsConstructibleFromZeroV<SafePtr>, "");

}  // namespace SafePtrTests
