#ifndef MOTOR_CONTROL_LAYER_LAYER_HPP
#error "This file must not be included directly, include motor_control_layer/layer.hpp instead"
#endif

#include "../device_layer/layer.hpp"

#include <device/control/controller.hpp>
#include <filter/pid.hpp>
#include <filter/shift.hpp>

namespace MotorControlLayer {
  namespace IntControl {

    class Dev : public DeviceLayer::Dev {
      using Lower = DeviceLayer::Dev;

      Filter::Proportional<s32> id{1};
      Filter::Derivate<s32> diff_l{0};
      Filter::Pid<s32> pid_l{0,1,0};
      Filter::Shift<s32, u8> shift_l{0};
      Filter::Chain<decltype(pid_l), decltype(shift_l)> err_l{pid_l, shift_l};

      Filter::Derivate<s32> diff_r{0};
      Filter::Pid<s32> pid_r{0,1,0};
      Filter::Shift<s32, u8> shift_r{0};
      Filter::Chain<decltype(pid_r), decltype(shift_r)> err_r{pid_r, shift_r};


    public:
      Device::Control::SystemController<
          RemoveRef<decltype(Lower::motor_left)>::Type, RemoveRef<decltype(Lower::encoder_left)>::Type,
          RemoveRef<decltype(id)>::Type, RemoveRef<decltype(diff_l)>::Type, RemoveRef<decltype(err_l)>::Type
          >
          motor_left{Lower::motor_left, Lower::encoder_left, id, diff_l, err_l};

      Device::Control::SystemController<
          RemoveRef<decltype(Lower::motor_left)>::Type, RemoveRef<decltype(Lower::encoder_left)>::Type,
          RemoveRef<decltype(id)>::Type, RemoveRef<decltype(diff_r)>::Type, RemoveRef<decltype(err_r)>::Type
          >
          motor_right{Lower::motor_right, Lower::encoder_right, id, diff_r, err_r};

      DECL_AUTO_ATTRIBUTE(updater_constructor, Lower::updater_constructor
                          .build(motor_left , 100000)
                          .build(motor_right, 100000)
                          );
    };

  }
}
