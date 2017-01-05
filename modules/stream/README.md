# Stream

This library is a part of the [Aversive++ project](https://github.com/AversivePlusPlus/AversivePlusPlus).

## Description

This library is the Aversive++'s Stream API definitions. A Stream is very similar to the concept of stream in C++'s `std` or C. Indeed, a basic Input or Output Stream will have some well known methods as read or write. A formatted Stream will have the C++'s `<<` operator.

No implementation is provided in this library, except for StringStream. If you need an implementation, please, check for other [Aversive++ modules](https://github.com/AversivePlusPlus) (starting with "stream-*", generally).

## Installation

This library has 2 dependencies : [Base](https://github.com/AversivePlusPlus/base) and [Container](https://github.com/AversivePlusPlus/container)

### Simple

Clone the git repository :
```bash
git clone https://github.com/AversivePlusPlus/base.git
git clone https://github.com/AversivePlusPlus/container.git
git clone https://github.com/AversivePlusPlus/stream.git
```

Since this library is header only, you can just add the compiler `-I` option to your project :
```bash
g++ myfile.cpp                 \
  -I/path/to/base/include      \
  -I/path/to/container/include \
  -I/path/to/stream/include
```

### Arduino (from sources)

Please note that this package use C++11, which is not enabled by default in most versions of the Arduino IDE. You may need to enable C++11 (google is your friend ;) ), or update the IDE.

This library has dependencies, you need to add all dependencies to the Arduino IDE.

Clone the git repository :
```bash
git clone https://github.com/AversivePlusPlus/stream.git
cd stream
make arduino_package
```

You will find the file `stream.zip` in `build` directory. 
You can add it to your Arduino IDE (sketch > include library > add .zip library)

## Use

A Stream is a class inherited from one of these three classes : 
```c++
class InputStream;  // getChar, read, readable
class OutputStream; // putChar, write, writable
class IOStream;     // fuuusion !
```

But there is some other interface classes that a Stream may follow :
```c++
class RandomAccessStream;   // write or read starting from a "cursor" (seek, cursor, move)
class InputBufferedStream;  // implementation of a buffer for input
class OutputBufferedStream; // implementation of a buffer for output
```

### StringStream

```c++
#include <stream/string_stream.hpp>
```

A StringStream is "just" a buffer of chars coated with the Stream API. It is not really useful as-is, but, decorated with FormattedStreamDecorator, it can be useful to tranform integers or other objects to strings.

```c++
u32 val = 42;
Stream::FormattedStringStream<4> fss;
fss << val;
char str[4];
fss.read(str, fss.readable()); // now str = "42"
```

### FormattedStreamDecorator

```c++
#include <stream/formatted_stream.hpp>
```

This is not really a stream, but a decorator.
It enables any stream to use th C++'s std::stream `<<` operator, to do formatted stream.
The behaviour remains differents from standard C++ streams, since the aim of this class is to have a low cost in memory and execution.

```c++
MyOutputStream os;
FormattedOutputStream<decltype(os)> fos(os);
fos << "my answer : " << 42 << "\n"
```
