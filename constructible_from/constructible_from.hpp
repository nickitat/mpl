#pragma once

#include "../type_traits/type_utilities.hpp"

#include <memory>
#include <type_traits>

namespace constructible_from {

template <template <typename> class... Preds>
struct Signature {};

namespace detail {

template <class Data, class DataType, class Dummy>
class ConstructibleFrom;

template <class Type, class DataType, template <typename> class... Preds>
class ConstructibleFrom<Type, DataType, Signature<Preds...>> {
  template <class... Args>
  static constexpr bool SizesMatch = sizeof...(Args) == sizeof...(Preds);

  template <class... Args>
  using CheckConstraints =
      std::enable_if_t<SizesMatch<Args...> && (... && Preds<Args&&>::value)>;

 public:
  // Should be present because presence of any user-declared constructor (it
  // is always there, since it is for what this class is intended) forbids
  // generation of implicitly declared default constructor. This default
  // constructors required because all the bases of
  // ::ConstructibleFrom::Type (except the one whose constructor will be
  // selected for the actual initialization) will be default-initialized.
  ConstructibleFrom() = default;

  template <class... Args, typename = CheckConstraints<Args...>>
  constexpr ConstructibleFrom(Args&&... args) noexcept(
      std::is_nothrow_constructible_v<DataType, Args...>) {
    // A bit of hackery. The entire Type object is not constructed yet and thus
    // accessing its member is not a good idea. But |mem| is not an own member
    // of Type, it is derived from Holder which is perfectly constructed to that
    // moment, since Holder is another base of Type, preceding ConstructibleFrom
    // in the base-specifier-list. I'm unable to argue about validity of this
    // code, but (maybe only from the technical side of the things) it seems to
    // be valid.
    auto theEntireObject = static_cast<Type*>(this);
    ::new ((void*)::std::addressof(theEntireObject->mem))
        DataType(std::forward<Args>(args)...);
  }
};

}  // namespace detail

template <class DataType, class... Signature>
class ConstructibleFrom {
  using AlignedStorage =
      std::aligned_storage_t<sizeof(DataType), alignof(DataType)>;

  struct Holder {
    DataType* const __mem() {
      return reinterpret_cast<DataType*>(::std::addressof(mem));
    }

    const DataType* const __mem() const {
      return reinterpret_cast<const DataType*>(::std::addressof(mem));
    }

    DataType& __ref() {
      return *__mem();
    }

    const DataType& __ref() const {
      return *__mem();
    }

    AlignedStorage mem;
  };

 public:
  struct Type : Holder,
                detail::ConstructibleFrom<Type, DataType, Signature>... {
    using detail::ConstructibleFrom<Type, DataType, Signature>::
        ConstructibleFrom...;

    operator DataType&() & {
      return Holder::__ref();
    }

    operator const DataType&() const& {
      return Holder::__ref();
    }

    operator const DataType&() && = delete;
  };

  // TODO: does this requirement guarantee that the trick inside
  // ConstructibleFrom's constructor is a perfectly valid code?
  static_assert(std::is_standard_layout_v<Type>,
                "Type is intended to be a standard layout type.");

  static_assert(sizeof(Type) == sizeof(DataType),
                "Size of Type should match the size of the DataType. EBO is "
                "guaranteed for standard layout types.");

  // DefaultZeroConstructible may work incorrectly without this two assumptions
  // being correct.
  static_assert(std::is_aggregate_v<AlignedStorage>,
                "AlignedStorage should be an aggregate.");
  static_assert(std::is_aggregate_v<Holder>, "Holder should be an aggregate.");
};

namespace traits {

// TODO: implement
// Makes Type default constructible, underlying storage will be
// zero-initialized.
template <class Type>
struct DefaultZeroConstructible;

// TODO: implement
// Makes Type not default constructible.
template <class Type>
struct NotDefaultConstructible;

}  // namespace traits

}  // namespace constructible_from
