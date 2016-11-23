# base

## Description

This project is a part of the [Aversive++ library](https://github.com/AversivePlusPlus/AversivePlusPlus).
This module is the base module of the library. 
It contains all basic types definitions (integers, array, booleans, etc...).
It also defines some metaprogramming structures that ares usefull in others modules (or even the user code).

## Types defines

### Basic types

#### Integers

```c++
#include <base/integer.hpp>
```

 - `u*` Unsigned integer where "*" is the size of the integer in bits. (ex : `u32`)
 - `s*` Signed integer. (ex : `s16`)
Available sizes : 8, 16, 32, 64

#### Compile-time integers

```c++
#include <base/compil.hpp>
```

This header defines integers values that can be evaluated at compile time.
These "Compil" integers can be handled similarly as a normal integer, but can be passed as a template parameter.

```c++
constexpr Compil<s32, 42> my_const;

// If you don't want a more "C-style" syntax : 
constexpr auto my_const = 42_cs32;
```

### Complex types

#### Arrays

```c++
#include <base/array.hpp>
```

The array behave like the C array, but with some more operators. 
Especially, the copy operator, that enables the user to copy an array without implementing the loop.

```c++
Array<2, u32> array1(1,2);
Array<2, u32> array2(9,8);

Array<2, u32> array3 = array1 + array2; // array3 = Array<2, u32>(10,10)
```

#### Pairs

```c++
#include <base/pair.hpp>
```

Pairs are, as in onther languages a structure with two values (left value, and right values), which can be of different types.

```c++
Pair<u8, s64> pair ('a', 400000000)
```
