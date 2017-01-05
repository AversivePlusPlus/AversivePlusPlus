#ifndef ROBOT_CONTROL_LAYER_LAYER_HPP
#define ROBOT_CONTROL_LAYER_LAYER_HPP

// Here is the template interface you need to follow if you want to implement a (better) version of this layer
/*
class Dev {
public:
  Device::Input<s32, ...> distance;
  Device::Input<s32, ...> angle;

  Device::Output<s32, ...> robot_distance;
  Device::Output<s32, ...> robot_angle;

  Stream::FormattedStreamDecorator<...> io{...};

  AsynchronousUpdaterConstructor updater_constructor;
};
*/

#include "int_control.hpp"

namespace RobotControlLayer {
  using namespace IntControl;
}

#endif//ROBOT_CONTROL_LAYER_LAYER_HPP
