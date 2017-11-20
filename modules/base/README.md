# Base

This library is a part of the [Aversive++ project](https://github.com/AversivePlusPlus/AversivePlusPlus).

## Description

The library defines some useful basic types (integers, fixed point numbers, arrays, pairs, matrix, etc..).
It also defines the well known type list metaprogramming structures, and the singleton pattern.

## Installation

### Simple

Clone the git repository :
```bash
git clone https://github.com/AversivePlusPlus/base.git
```

Since this library is header only, you can just add the compiler `-I` option to your project :
```bash
g++ -I/path/to/base/include myfile.cpp
```

### Arduino (from sources)

Please note that this package use C++11, which is not enabled by default in most versions of the Arduino IDE. You may need to enable C++11 (google is your friend ;) ), or update the IDE.

Clone the git repository :
```bash
git clone https://github.com/AversivePlusPlus/base.git
cd base
make arduino_package
```

You will find the file `base.zip` in `build` directory. 
You can add it to your Arduino IDE (sketch > include library > add .zip library)

### With Conan package system

If you are a [conan](https://github.com/conan-io/conan) user, you can export the conan package :
```bash
git clone https://github.com/AversivePlusPlus/base.git
cd base && conan export AversivePlusPlus/dev
```

And add this to the `requires` field of your conanfile : 
```yaml
base/0.1@AversivePlusPlus/dev
```

## Use

### Integers

```c++
#include <base/integer.hpp>
```

It basically defines shorter names for the standard `stdint.h`. Why ? Because in `uint32_t`, 5 characters are useless ;)

```c++
u32 var1; // equivalent to uint32_t
s16 var2; // equivalent to int16_t
```

### Compile-time integers

```c++
#include <base/compil.hpp>
```

This header defines integers values that can be evaluated at compile time.
These "Compil" integers can be handled similarly as a normal integer, but can be passed as a template parameter.

```c++
Compil<s32, 42> my_const;

// If you can't stand templates : 
auto my_const = 42_cs32;
```

### Arrays

```c++
#include <base/array.hpp>
```

The array behave like the C array, but with some more operators.

```c++
Array<u32, 2> array1(1,3);
Array<u32, 2> array2(9,8);

Array<u32, 2> array3 = array1 + array2; // array3 = Array<2, u32>(10,11);
```

### Pairs

```c++
#include <base/pair.hpp>
```

Pairs are, as in other languages a structure with two values (left value, and right values), which can be of different types.

```c++
Pair<u8, s64> pair('a', 400000000);
u8 tmp1 = pair.left();
s64 tmp2 = pair.right();
```

### Matrix

```c++
#include <base/matrix.hpp>
```

Matrix are useful mathematical object. Most of basic operations on matrix are available.

```c++
Matrix<double, 3,1> vec(10,0,0);

double tmp1 = vec[2][0];
double tmp2 = vec(1,0);  // better

Matrix<double, 3,3> mat(
  5,0,0,
  0,1,0,
  0,0,1
  );

auto vec2 = mat*vec; // vec2 = Matrix<double, 3,1>(50,0,0);
```

### Singleton

```c++
#include <base/singleton.hpp>
```

The singleton pattern !

```c++
class MySingleton : public Singleton<MySingleton> {
  // Awesome stuff
};
```
