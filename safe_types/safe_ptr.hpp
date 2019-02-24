#pragma once

#include "../constructible_from/constructible_from.hpp"
#include "../type_traits/type_traits.hpp"

#include <type_traits>

namespace safe_types {

namespace detail {

template <class UnderlyingType>
class SafePtr {
  using UnderlyingPtrType = std::add_pointer_t<UnderlyingType>;

  template <class Rhs>
  using MatchUnderlyingPtr = MatchAnyRef<UnderlyingPtrType, Rhs>;

  template <class Rhs>
  using MatchNullptrT = MatchAnyRef<std::nullptr_t, Rhs>;

 public:
  using Type = typename constructible_from::ConstructibleFrom<
      UnderlyingPtrType,
      Domains<MatchUnderlyingPtr>,
      Domains<MatchNullptrT>>::Type;
};

}  // namespace detail

template <class UnderlyingType>
using SafePtr = typename detail::SafePtr<UnderlyingType>::Type;

}  // namespace safe_types
