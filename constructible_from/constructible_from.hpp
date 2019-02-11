#pragma once

#include <type_traits>

template <template <typename> class... ConstructionArgs>
struct Domain {};

namespace detail {

// template <class DataType,
//           template <template <typename> class... Args> class... Domains>
// struct Receiver {};

template <class Data, class T, class Dummy>
struct ConstructibleFrom;

template <class Data, class T, template <typename> class... Rules>
struct ConstructibleFrom<Data, T, Domain<Rules...>> {
  // Seems like empty Args is a special case, since it has no types that violate
  // the Rules. But what to do with default-constructible parameters? Maybe we
  // should check sizeof...(Rules) and conditionally permit this constructor?
  constexpr ConstructibleFrom() = delete;

  template <class... Args,
            typename = std::enable_if_t<(... && Rules<Args>::value)>>
  constexpr ConstructibleFrom(Args... args) noexcept(
      std::is_nothrow_constructible_v<T, Args...>) {
    // A bit of hackery. The whole Data object is not
    // constructed yet and thus accessing its member
    // is not a good idea (precisely, UB). But |mem|
    // is not an own member of Data, it is derived
    // from Holder which is perfectly constructed to
    // that moment, since Holder is another base of
    // Data, preceding ConstructibleFrom in the
    // base-specifier-list.
    auto dataPtr = static_cast<Data*>(this);
    new (&dataPtr->mem) T{std::forward<Args>(args)...};
  }
};

}  // namespace detail

template <class DataType, class... Domains>
class ConstructibleFrom {
 public:
  struct Type;

 private:
  using AlignedStorage =
      std::aligned_storage_t<sizeof(DataType), alignof(DataType)>;

  //   using ConstructionTrait =
  //       detail::ConstructibleFrom<Type, DataType, ConstructionArgs...>;

  struct Holder {
    AlignedStorage mem;
  };

 public:
  // The constructor of ConstructionTrait became the only possible constructor
  // for Type, since it have no own constructors.
  // Also note that detail::ConstructibleFrom is not an aggregate type, so it
  // can be initialized only through constructor call.
  struct Type : Holder, detail::ConstructibleFrom<Type, DataType, Domains>... {
    using detail::ConstructibleFrom<Type, DataType, Domains>::
        ConstructibleFrom...;

    operator DataType() {
      return *reinterpret_cast<DataType*>(&this->mem);
    }
  };
};
