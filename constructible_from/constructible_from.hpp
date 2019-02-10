#pragma once

#include <type_traits>

namespace detail {

template <class Data, class T, class... Args>
struct ConstructibleFrom {
  constexpr ConstructibleFrom(Args... args) noexcept(
      std::is_nothrow_constructible_v<T, Args...>) {
    // A bit of hackery. The whole Data object is not constructed
    // yet and thus accessing its member is not a good idea (precisely, UB). But
    // |mem| is not an own member of Data, it is derived from Holder which is
    // perfectly constructed to that moment, since Holder is another base of
    // Data, preceding ConstructibleFrom in the base-specifier-list.
    auto dataPtr = static_cast<Data*>(this);
    new (&dataPtr->mem) T(std::forward<Args>(args)...);
  }
};

}  // namespace detail

template <class DataType, class... ConstructionArgs>
class ConstructibleFrom {
 public:
  struct Type;

 private:
  using AlignedStorage =
      std::aligned_storage_t<sizeof(DataType), alignof(DataType)>;

  using ConstructionTrait =
      detail::ConstructibleFrom<Type, DataType, ConstructionArgs...>;

  struct Holder {
    AlignedStorage mem;
  };

 public:
  // The constructor of ConstructionTrait became the only possible constructor
  // for Type, since it have no own constructors.
  // Also note that detail::ConstructibleFrom is not an aggregate type, so it
  // can be initialized only through constructor call.
  struct Type : Holder, ConstructionTrait {
    using ConstructionTrait::ConstructionTrait;

    operator DataType() {
      return *reinterpret_cast<DataType*>(&this->mem);
    }
  };
};
