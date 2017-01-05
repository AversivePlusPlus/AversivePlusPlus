#ifndef ROBOT_CONTROL_LAYER_LAYER_HPP
#error "This file must not be included directly, include robot_control_layer/layer.hpp instead"
#endif

#include "../motor_control_layer/layer.hpp"

#include <device/control/controller.hpp>
#include <device/control/input_filter.hpp>
#include <device/control/output_filter.hpp>
#include <filter/pid.hpp>
#include <filter/shift.hpp>
#include <filter/quadramp.hpp>

#include <device/2wheel/odometer.hpp>
#include <device/2wheel/robot.hpp>

namespace RobotControlLayer {
  namespace IntControl {

    class Dev : public MotorControlLayer::Dev {
      using Lower = MotorControlLayer::Dev;

      Filter::Proportional<s32> id{1};

      Filter::Pid<s32> pid_d{0,1500,0,6000};
      Filter::Shift<s32, u8> shift_d{15};
      Filter::Chain<decltype(pid_d), decltype(shift_d)> err_d{pid_d, shift_d};

      Filter::Quadramp<s32> qramp_d{0, -400, 400, 40, 40};

      Filter::Derivate<s32> diff_a{0};
      Filter::Pid<s32> pid_a{0,800,0,10000};
      Filter::Shift<s32, u8> shift_a{15};
      Filter::Chain<decltype(pid_a), decltype(shift_a)> err_a{pid_a, shift_a};

      Filter::Quadramp<s32> qramp_a{0, -40, 40, 2, 2};

      using Odo = Device::TwoWheel::Odometer<s32, decltype(Lower::encoder_left), decltype(Lower::encoder_right)>;
      Odo odo{Lower::encoder_left, Lower::encoder_right};

      using Bot = Device::TwoWheel::Robot<s32, decltype(Lower::motor_left), decltype(Lower::motor_right)>;
      Bot bot{Lower::motor_left, Lower::motor_right};

      Bot::Distance bot_dist{bot};
      Bot::Angle bot_angle{bot};

      Odo::Angle odo_angle{odo};
      Filter::Proportional<s32> paf{2347};
      Filter::Shift<s32, s32> saf{10};
      Filter::Chain<decltype(paf), decltype(saf)> af{paf, saf};

      Filter::Derivate<s32> diff_d{0};

    public:
      Odo::Distance distance{odo};
      Device::Control::InputFilter<decltype(odo_angle), decltype(af)> angle {odo_angle, af};

      Device::Control::SystemController<
          RemoveRef<decltype(bot_dist)>::Type, RemoveRef<decltype(distance)>::Type,
          RemoveRef<decltype(qramp_d)>::Type, RemoveRef<decltype(diff_d)>::Type, RemoveRef<decltype(err_d)>::Type
          >
          robot_speed{bot_dist, distance, qramp_d, diff_d, err_d};

      Device::Control::SystemController<
          RemoveRef<decltype(bot_angle)>::Type, RemoveRef<decltype(angle)>::Type,
          RemoveRef<decltype(qramp_a)>::Type, RemoveRef<decltype(id)>::Type, RemoveRef<decltype(err_a)>::Type
          >
          robot_angle{bot_angle, angle, qramp_a, id, err_a};

      DECL_AUTO_ATTRIBUTE(updater_constructor, Lower::updater_constructor
                          .build(bot, 100000)
                          .build(robot_speed, 100000)
                          .build(robot_angle, 100000)
                          );
    };

  }
}
