#pragma once

#include <memory>
#include <type_traits>

template <template <typename> class... Rules>
struct Domains {};

namespace detail {

// template <class DataType,
//           template <template <typename> class... Args> class... Domains>
// struct Receiver {};

template <class Data, class T, class Dummy>
struct ConstructibleFrom;

template <class Data, class T, template <typename> class... Rules>
struct ConstructibleFrom<Data, T, Domains<Rules...>> {
  // Seems like empty Args is a special case, since it has no types that violate
  // the Rules. But what to do with default-constructible parameters? Maybe we
  // should check sizeof...(Rules) and conditionally permit this constructor?
  // EDIT: maybe we should have default_constructible_tag, cause special
  // constructors can not be inherited.
  ConstructibleFrom() = default;

  template <class... Args,
            typename = std::enable_if_t<sizeof...(Args) == sizeof...(Rules) &&
                                        (... && Rules<Args>::value)>>
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
    ::new ((void*)::std::addressof(dataPtr->mem))
        T(std::forward<Args>(args)...);
  }
};

}  // namespace detail

template <class DataType,
          class... Domains /*, bool isDefaultConstructible = false*/>
class ConstructibleFrom {
 public:
  struct Type;

 private:
  using AlignedStorage =
      std::aligned_storage_t<sizeof(DataType), alignof(DataType)>;

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
