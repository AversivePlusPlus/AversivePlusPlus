#ifndef ABSOLUTE_CONTROL_LAYER_LAYER_HPP
#define ABSOLUTE_CONTROL_LAYER_LAYER_HPP

// Here is the template interface you need to follow if you want to implement a (better) version of this layer
/*
class Dev {
public:
  Device::Input<s32, ...> x;
  Device::Input<s32, ...> y;
  Device::Input<s32, ...> a;

  Device::Output<s32, ...> speed_x;
  Device::Output<s32, ...> speed_y;

  Stream::FormattedStreamDecorator<...> io{...};

  AsynchronousUpdaterConstructor updater_constructor;
};
*/

#include "int_control.hpp"

namespace AbsoluteControlLayer {
  using namespace IntControl;
}

#endif//ABSOLUTE_CONTROL_LAYER_LAYER_HPP
