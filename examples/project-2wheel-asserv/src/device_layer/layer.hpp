#ifndef DEVICE_LAYER_LAYER_HPP
#define DEVICE_LAYER_LAYER_HPP

// Here is the template interface you need to follow if you want to port this project to your robot.
/*
class Dev {
public:
  Device::Input<s32, ...> encoder_left;
  Device::Input<s32, ...> encoder_right;

  Device::Output<s32, ...> motor_left;
  Device::Output<s32, ...> motor_right;

  Stream::FormattedStreamDecorator<...> io{...};

  AsynchronousUpdaterConstructor& updater_constructor;
};
*/

#ifdef AVERSIVE_TOOLCHAIN_SASIAE
#include "tiny_sasiae.hpp"
#else
#error "Target not supported by this project"
#endif

#endif//DEVICE_LAYER_LAYER_HPP
