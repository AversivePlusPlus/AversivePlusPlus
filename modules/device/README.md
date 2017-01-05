# Device

This library is a part of the [Aversive++ project](https://github.com/AversivePlusPlus/AversivePlusPlus).

## Description

This library is the Device API definition.
A Device represents a way for the program to communicate with the external world (The word "Device" mean "System" in a mechanical point of view, in robotics, for example).
A Device is designed to send or receive some very basic information (an integer or a double, mainly).

This library is very useful for making a custom driver (made specially for your robot's hardware, for example) compatible with other drivers of Aversive++.

The API is really simple and consist in two base class : 
```c++
template<typename T> Input<T>;  // A sensor
template<typename T> Output<T>; // An actuator
```

And two virtual functions : 
```c++
template<typename T> T Input<T>::getValue(void);  // Get the value from a sensor
template<typename T> void Output<T>::setValue(T); // Send the value to an actuator
```

## Installation

### Simple

Clone the git repositories :
```bash
git clone https://github.com/AversivePlusPlus/device.git
```

Since this library is header only, you can just add the compiler `-I` option to your project :
```bash
g++ -I/path/to/device/include myfile.cpp
```

## Use

To create a new (simple) Device, you just need to inherit the class from one of the two previous.
For example, with a sensor :

```c++
#include <device/input.hpp>

class MyUltimateAnswer : public Input<u32> {
  u32 getValue(void) {
    return 42;
  }
};
```
