# Device

## Description

This project is a part of the [Aversive++ library](https://github.com/AversivePlusPlus/AversivePlusPlus).
This module is the Device API definition.

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
