#pragma once

#include <type_traits>

namespace detail {

template <class To>
void test(To);

template <class From, class To, typename = void>
struct IsNonnarrowingConvertible : std::false_type {};

template <class From, class To>
struct IsNonnarrowingConvertible<From,
                                 To,
                                 decltype(test<To>({std::declval<From>()}))>
    : std::true_type {};

}  // namespace detail

template <class From, class To, typename = void>
static constexpr bool IsNonnarrowingConvertible =
    detail::IsNonnarrowingConvertible<From, To>::value;
