[![Build Status](https://travis-ci.com/nickitat/mpl.svg?branch=master)](https://travis-ci.com/nickitat/mpl)

# mpl
It is a small area where I want to learn C++ and especially various metaprogramming techniques,
being trying my best to create something interesting in addition.

# content
* `ConstructibleFrom` - is a facility which allows you to create a type with the given set of possible constructors. Each constructor is described by its `Signature`. For example, providing a `Signature<Pred1, Pred2>` among the template parameters of the given `ConstructibleFrom` instanse means that it will be possible to create an object of the resulting type from any two arguments suttisfying the `Pred1` and `Pred2` respectively.\
Refer to the safe_type folder to see a few exemplary applications of `ConstructibleFrom`.
* `Safe types` - are some types (usually equivalent to some builtin types) modified somehow to make them more "safe" to use. For example, `SafeInt` is the type principally equivalent to the standard `int` but it can not be constructed (and assigned to) through narrowing conversion.
