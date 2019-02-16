#pragma once

#include <memory>
#include <type_traits>

template <template <typename> class... Rules>
struct Domains {};

namespace detail {

template <class Data, class DataType, class Dummy>
class ConstructibleFrom;

template <class Type, class DataType, template <typename> class... Rules>
class ConstructibleFrom<Type, DataType, Domains<Rules...>> {
  template <class... Args>
  static constexpr bool SizesMatch = sizeof...(Args) == sizeof...(Rules);

  template <class... Args>
  using CheckConstraints =
      std::enable_if_t<SizesMatch<Args...> && (... && Rules<Args>::value)>;

 public:
  // Should be present because presence of any user-declared constructor (it
  // is always there, since it is for what this class is intended) forbids
  // generation of implicitly declared default constructor. This default
  // constructors required because all the bases of
  // ::ConstructibleFrom::Type (except the one whose constructor will be
  // selected for the actual initialization) will be default-initialized.
  ConstructibleFrom() = default;

  template <class... Args, typename = CheckConstraints<Args...>>
  constexpr ConstructibleFrom(Args... args) noexcept(
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

template <class DataType,
          class... Domains /*, bool isDefaultConstructible = false*/>
class ConstructibleFrom {
  using AlignedStorage =
      std::aligned_storage_t<sizeof(DataType), alignof(DataType)>;

  struct Holder {
    AlignedStorage mem;
  };

 public:
  struct Type : Holder, detail::ConstructibleFrom<Type, DataType, Domains>... {
    using detail::ConstructibleFrom<Type, DataType, Domains>::
        ConstructibleFrom...;

    operator DataType() {
      return *reinterpret_cast<DataType*>(&this->mem);
    }
  };

  static_assert(sizeof(Type) == sizeof(DataType),
                "Size of Type should match size of the DataType.");
};
