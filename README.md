# mpl
It is a small area where I want to learn C++ and especially various metaprogramming techniques,
being trying my best to create something interesting in addition.

# content
* `ConstructibleFrom` - is a facility which allows you to create a type with the given set of possible construction args.
It is related to smth known as "safe types". See `ConstructibleFrom`'s readme.
* `Safe types` - are some types (usually equivalent to some builtin types) modified somehow to make them more "safe" to use. For example, `SafeInt` is the type principally equivalent to the standard `int` but it can not be constructed (and assigned to) through narrowing conversion.
