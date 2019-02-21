#pragma once

#include <type_traits>

namespace type_traits {

namespace detail {

template <class T>
void __test_1(T);
}

namespace detail {

template <class From, class To, typename = void>
struct IsNonnarrowingConvertible : std::false_type {};

template <class From, class To>
struct IsNonnarrowingConvertible<From,
                                 To,
                                 decltype(__test_1<To>({std::declval<From>()}))>
    : std::true_type {};

}  // namespace detail

namespace detail {

template <class T, typename = void, typename = void>
struct IsConstructibleFromZero : std::false_type {};

template <class T>
struct IsConstructibleFromZero<T,
                               std::enable_if_t<std::is_integral_v<T>>,
                               decltype(__test_1<T>(0))> : std::true_type {};

template <class T>
struct IsConstructibleFromZero<T,
                               std::enable_if_t<!std::is_integral_v<T>>,
                               decltype(__test_1<T>({0}))> : std::true_type {};

}  // namespace detail

template <class From, class To>
using IsNonnarrowingConvertible = detail::IsNonnarrowingConvertible<From, To>;

template <class From, class To>
static constexpr bool IsNonnarrowingConvertibleV =
    IsNonnarrowingConvertible<From, To>::value;

template <class T>
using IsConstructibleFromZero = detail::IsConstructibleFromZero<T>;

template <class T>
static constexpr bool IsConstructibleFromZeroV =
    detail::IsConstructibleFromZero<T>::value;

}  // namespace type_traits
