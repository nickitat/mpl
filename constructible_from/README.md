### Rationale

#### Type

Conversion to `const DataType&` from rvalue of type `ConstructibleFrom<...>::Type` is prohibited. There is hardly exist a case when it would not lead to having a dangling reference as the result.
```cpp
using MyInt = ConstructibleFrom<int, ...>;

const int& dangRef = MyInt{42};
```
If rvalue-s of type `MyInt` were convertible to `int&`, you would be able to grab a reference to the underlying storage
of `MyInt`'s temporary. But the lifetime of that temporary is sticked to the end of the full expression where it was introduced.
