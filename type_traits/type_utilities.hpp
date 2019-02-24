#pragma once

#include <type_traits>

namespace type_traits {

template <class... Preds>
struct Disjunction {
  static constexpr bool value = (... || Preds::value);
};

template <class... Preds>
struct Conjunction {
  static constexpr bool value = (... && Preds::value);
};

template <class Pred>
struct Not {
  static constexpr bool value = !Pred::value;
};

template <class Lhs, class Rhs>
using MatchLRef = std::is_same<std::add_lvalue_reference_t<Lhs>, Rhs>;

template <class Lhs, class Rhs>
using MatchRRef = std::is_same<std::add_rvalue_reference_t<Lhs>, Rhs>;

template <class Lhs, class Rhs>
using MatchAnyRef = Disjunction<MatchLRef<Lhs, Rhs>, MatchRRef<Lhs, Rhs>>;

}  // namespace type_traits