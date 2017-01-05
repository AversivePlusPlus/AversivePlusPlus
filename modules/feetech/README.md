# Feetech

This library is a part of the [Aversive++ project](https://github.com/AversivePlusPlus/AversivePlusPlus).

## Description

This library provides drivers for Feetech's SCS15 servomotors (others motors may be complatible but are not tested).
The library doesn't provide an UART driver (which is microcontroller specific), but is compatible with Aversive++'s Stream API, so that using an existing driver or making your own is easy !

## Installation

This library has 3 dependencies : 
[Base](https://github.com/AversivePlusPlus/base), 
[Container](https://github.com/AversivePlusPlus/container) and
[Stream](https://github.com/AversivePlusPlus/stream)

### Simple

Clone the git repository :
```bash
git clone https://github.com/AversivePlusPlus/base.git
git clone https://github.com/AversivePlusPlus/container.git
git clone https://github.com/AversivePlusPlus/stream.git
git clone https://github.com/AversivePlusPlus/feetech.git
```

Since this library is header only, you can just add the compiler `-I` option to your project :
```bash
g++ myfile.cpp                 \
  -I/path/to/base/include      \
  -I/path/to/container/include \
  -I/path/to/stream/include    \
  -I/path/to/feetech/include
```

### Arduino (from sources)

Please note that this package use C++11, which is not enabled by default in most versions of the Arduino IDE. You may need to enable C++11 (google is your friend ;) ), or update the IDE.

This library has dependencies, you need to add all dependencies to the Arduino IDE.

Clone the git repository :
```bash
git clone https://github.com/AversivePlusPlus/feetech.git
cd feetech
make arduino_package
```

You will find the file `feetech.zip` in `build` directory. 
You can add it to your Arduino IDE (sketch > include library > add .zip library)

## Use

### SC interface

```c++
#include <feetech/sc.hpp>
```

This library is based on the Arduino library provided by the vendor.
There is a SC object that implements an interface for most common use (not all).
If you want to make an other register accessible, please, see the SC class implementation.

```c++
SomeUART uart;
Feetech::SC<decltype(uart)> sc(uart);

if(sc.ping(1)) { // will return true a servo with address 1 answered
  sc.setId(1, 2);
  sc.enableTorque(2);
  sc.setPosition(2, 512);
  bool en = sc.isTorqueEnabled(2);
  u16 pos = sc.getPosition(2);
  s16 load = sc.getLoad(2);
  s16 spe = sc.getSpeed(2);
}
```

### Make your own UART Driver compatible

You need to provide an Input and Output [Stream](https://github.com/AversivePlusPlus/stream) to be used with this driver.
Let's take an example with a previouly implemented C uart driver : 

```c
uart_init(int uart_id, int baudrate);
uart_write(int uart_id, char* data, int length);
uart_read(int uart_id, char* data, int length);
```


```c++
class UARTStream :
  public Stream::OutputStream<UARTStream>,
  public Stream::InputStream<UARTStream> {

private:
  const uart_t _uart_id;
  
public:
  inline UARTStream(uart_t uart_id, u32 baudrate)
    : _uart_id(uart_id) {
    uart_init(_uart_id, baudrate);
  }

  inline void putChar(u8 c) {
    uart_write(_uart_id, &c, 1);
  }

  inline u16 write(u8* data, u16 length) {
    uart_write(_uart_id, data, length);
    return length;
  }

  inline u16 writable(void) {
    return 1;
  }

  inline u8 getChar(void) {
    char c = 0;
    uart_read(_uart_id, &c, 1);
    return (u8)c;
  }

  inline u16 read(u8* data, u16 length) {
    uart_read(_uart_id, data, length);
    return length;
  }

  inline u16 readable(void) {
    return 1;
  }
};
```
