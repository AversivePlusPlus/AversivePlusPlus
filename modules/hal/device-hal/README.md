# Device HAL

## Description

This project is a part of the [Aversive++ library](https://github.com/AversivePlusPlus/AversivePlusPlus).
This module follow the Device API, and defines Devices on top of HAL interface.

## Devices

### Encoder

A Device based on HAL ENCODER.

```c++
#include <device/hal/encoder.hpp>

struct MyEncoderSettings : Device::DefaultEncoderSettings {
  // WARNING : You must check in the datasheet if the PINs and TIMER can be used together as ENCODER
  constexpr auto& timer = TIMER1; // for example
  constexpr auto& channel1 = A1; // for example
  constexpr auto& channel2 = A2; // for example
}

Encoder<MyEncoderSettings> encoder;
u32 val = encoder.getValue(); // get the counter's value (u32)
encoder.reset();              // to reset the counter to 0
```

### InputDigitalPin

A Device based on HAL GPIO, when using a PIN in INPUT Mode.

```c++
#include <device/hal/input_digital_pin.hpp>

struct MyPinSettings : Device::DefaultInputDigitalPinSettings {
  constexpr auto& pin = A1; // for example
}

InputDigitalPin<MyPinSettings> pin;
bool val = pin.getValue();
```

### OutputDigitalPin

A Device based on HAL GPIO, when using a PIN in OUTPUT Mode.

```c++
#include <device/hal/output_digital_pin.hpp>

struct MyPinSettings : Device::DefaultOutputDigitalPinSettings {
  constexpr auto& pin = A1; // for example
}

OutputDigitalPin<MyPinSettings> pin;
pin.setValue(true);
```

### PWMPin

A Device based on HAL PWM.

```c++
#include <device/hal/pwm_pin.hpp>

struct MyPWMSettings : Device::DefaultPWMPinSettings {
  // WARNING : You must check in the datasheet if the PIN and TIMER channel can be used together as PWM
  constexpr auto& pwm = TIMER1_CH1; // for example
  constexpr auto& pin = A1;         // for example
}

OutputDigitalPin<MyPWMSettings> pin;
pin.setValue(10); // Value in us
```
