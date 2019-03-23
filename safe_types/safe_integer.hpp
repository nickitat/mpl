#pragma once

#include <constructible_from/constructible_from.hpp>
#include <type_traits/type_traits.hpp>

namespace safe_types {

namespace detail {

template <class UnderlyingIntType>
class SafeInt {
  template <class From>
  using NonnarrowingConvertibleToUnderlyingInt =
      type_traits::IsNonnarrowingConvertible<From, UnderlyingIntType>;

 public:
  using Type = typename constructible_from::ConstructibleFrom<
      UnderlyingIntType,
      Signature<NonnarrowingConvertibleToUnderlyingInt>>::Type;
};

}  // namespace detail

template <class UnderlyingIntType>
using SafeInt = typename detail::SafeInt<UnderlyingIntType>::Type;

}  // namespace safe_types
