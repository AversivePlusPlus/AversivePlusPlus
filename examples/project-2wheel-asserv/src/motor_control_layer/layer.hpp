#ifndef MOTOR_CONTROL_LAYER_LAYER_HPP
#define MOTOR_CONTROL_LAYER_LAYER_HPP

// Here is the template interface you need to follow if you want to implement a (better) version of this layer
/*
class Dev {
public:
  Device::Input<s32, ...> encoder_left;
  Device::Input<s32, ...> encoder_right;

  Device::Output<s32, ...> motc_left;
  Device::Output<s32, ...> motc_right;

  Stream::FormattedStreamDecorator<...> io{...};

  AsynchronousUpdaterConstructor updater_constructor;
};
*/

#include "int_control.hpp"

namespace MotorControlLayer {
  using namespace IntControl;
}

#endif//MOTOR_CONTROL_LAYER_LAYER_HPP
