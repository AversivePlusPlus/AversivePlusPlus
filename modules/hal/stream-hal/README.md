# Stream HAL

## Description

This project is a part of the [Aversive++ library](https://github.com/AversivePlusPlus/AversivePlusPlus).
This module follow the Stream API, and defines Streams on top of HAL interface.

## Streams

### InputUARTStream

A Stream based on HAL UART with only RX.

```c++
#include <stream/hal/uart_stream.hpp>

struct MyUARTSettings : Device::DefaultUARTSettings {
  // WARNING : You must check in the datasheet if the PINs and UART can be used together
  constexpr auto& uart = SERIAL_UART1; // for example
  constexpr auto& rx = A1; // for example
}

InputUARTStream<MyUARTSettings> uart;
u8 buff[32];
uart.read(buff, 32);
```

### OutputUARTStream

A Stream based on HAL UART with only TX.

```c++
#include <stream/hal/uart_stream.hpp>

struct MyUARTSettings : Device::DefaultUARTSettings {
  // WARNING : You must check in the datasheet if the PINs and UART can be used together
  constexpr auto& uart = SERIAL_UART1; // for example
  constexpr auto& tx = A2; // for example
}

OutputUARTStream<MyUARTSettings> uart;
uart.write("test", sizeof("test"));
```

### UARTStream

A Stream based on HAL UART.

```c++
#include <stream/hal/uart_stream.hpp>

struct MyUARTSettings : Device::DefaultUARTSettings {
  // WARNING : You must check in the datasheet if the PINs and UART can be used together
  constexpr auto& uart = SERIAL_UART1; // for example
  constexpr auto& rx = A1; // for example
  constexpr auto& tx = A2; // for example
}

UARTStream<MyUARTSettings> uart;
```

### FormattedUARTStream

The previous streams can be decorated with FormattedStreamDecorator.
It exists in three versions (Input, Output, and "IO").

```c++
#include <stream/hal/uart_stream.hpp>

FormattedUARTStream<MyUARTSettings> uart;
s16 value;
uart >> value;
uart << (value + 1) << "\n";
```
