# Stream

## Description

This project is a part of the [Aversive++ library](https://github.com/AversivePlusPlus/AversivePlusPlus).
This module is the Stream API definitions.

A Stream is a class inherited from one of these three classes : 
```c++
class InputStream;
class OutputStream;
class IOStream;
```

But there is some other interface classes that a Stream may follow.

## Interfaces

### InputStream

A stream that can receive data.
It has 2 methods : 

```c++
u8 InputStream::getChar(void);
u16 InputStream::read(u8* data, u16 length);
```

To implement this kind of Stream, you just need to implement these two methods.

### OutputStream

A Stream that can send data.
It has 2 methods : 

```c++
void OutputStream::putChar(u8 c);
u16 OutputStream::write(u8* data, u16 length);
```

To implement this kind of Stream, you just need to implement these two methods.

### IOStream

Just a class that inherits from the two previous.

### RandomAccessStream

A Stream that can read or write at any address.
It uses the "seek" interface :

```c++
void RandomAccessStream::seek(u16 pos);
void RandomAccessStream::move(s16 offset);
u16 RandomAccessStream::cursor(void) const;
```

### InputBufferedStream

An InputStream that has some more methods for managing buffers : 

```c++
void InputBufferedStream::flushInput(void)
u16 InputBufferedStream::inputBufferSize(void) const
u16 InputBufferedStream::readable(void) const {
```

To implement this kind of Stream, you can't implement the `getChar` and `read` methods.
You will need to manage some (kind of) interruption that will fill the buffer.

### OutputBufferedStream

An OutputStream that has some more methods for managing buffers :

```c++
void OutputBufferedStream::flushOutput(void) const;
u16 OutputBufferedStream::outputBufferSize(void) const;
u16 OutputBufferedStream::writable(void) const;
```

To implement this kind of Stream, you can't implement the `putChar` and `write` methods.
You will need to manage some (kind of) interruption that will fill the buffer.
The implementation of the buffer will call an "interruption starter" that you must implement : 

```c++
void OutputBufferedStream::writeBeginHandler(void);
```

### FormattedStreamDecorator

A "stdlibc++ like" Stream.
It implements the std::stream operators : 

```c++
FormattedStream& FormattedStream::operator<<(...);
FormattedStream& FormattedStream::operator>>(...);
```

This is a decorator. You don't need to inherit from this class to be able to have a FormattedStream.
You can use any Stream to transform it into a formatted stream.
