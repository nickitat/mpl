#pragma once

#include <constructible_from/constructible_from.hpp>
#include <type_traits/type_traits.hpp>

#include <functional>
#include <type_traits>

namespace safe_types {

namespace detail {

template <class UnderlyingType>
class SafeRef {
  using UnderlyingRefType = std::reference_wrapper<UnderlyingType>;

  template <class Rhs>
  using MatchUnderlyingType = MatchLRef<UnderlyingType, Rhs>;

 public:
  using Type = typename constructible_from::
      ConstructibleFrom<UnderlyingRefType, Signature<MatchUnderlyingType>>::Type;
};

}  // namespace detail

template <class UnderlyingType>
using SafeRef = typename detail::SafeRef<UnderlyingType>::Type;

}  // namespace safe_types
