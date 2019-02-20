#pragma once

#include "../constructible_from/constructible_from.hpp"
#include "../type_traits/type_traits.hpp"

namespace safe_types {

namespace detail {

template <class UnderlyingPtrType>
class SafePtr {
  template <class Rhs>
  using MatchUnderlyingPtr = std::is_same<UnderlyingPtrType, Rhs>;

  template <class Rhs>
  using MatchNullptrT = std::is_same<std::nullptr_t, Rhs>;

 public:
  using Type = typename constructible_from::ConstructibleFrom<
      UnderlyingPtrType,
      Domains<MatchUnderlyingPtr>,
      Domains<MatchNullptrT>>::Type;
};

}  // namespace detail

template <class UnderlyingPtrType>
using SafePtr = typename detail::SafeInt<UnderlyingPtrType>::Type;

}  // namespace safe_types
